<script setup>
import { onMounted, reactive, ref, watch } from 'vue';
import AdjustmentItem from '~/components/AdjustmentItem.vue';
import SelectList from '~/components/SelectList.vue';
import SliderItem from '~/components/SliderItem.vue';
import TextInput from '~/components/TextInput.vue';
import GroupItem from '~/components/base/GroupItem.vue';
import Light from '~/components/icon/Light.vue';
import Send from '~/components/icon/Send.vue';
import Speed from '~/components/icon/Speed.vue';
import Pencil from '~/components/icon/Pencil.vue';
import MenuItem from '~/components/menuItem.vue';
import { TextScreenService } from '~/services';
import { StringData } from '~/utlis';
import Effect from '~/components/icon/Effect.vue';
import ColorPicker from '~/components/ColorPicker.vue';
const showSelectFont = ref(false)
const showSelectColorType = ref(false)
const selectedFont = ref()
const selectedColorType = ref()
const textScreenData = reactive({
  text: undefined,
  brightness: undefined,
  yPosition: undefined,
  lengthTextInByte: undefined,
  tick: undefined,
  font: undefined,
  color:undefined,
  colorType: undefined,

})
onMounted(async () => {
  const result = await TextScreenService.getScreenText()
  textScreenData.text = result['text']
  textScreenData.yPosition = result['yPosition']
  textScreenData.tick = result['tick']
  textScreenData.brightness = result['brightness']
  textScreenData.font = result['font']
  textScreenData.colorType = result['colorType']


  selectedColorType.value = StringData.colorTypeToString(textScreenData.colorType)
  selectedFont.value = StringData.fontNameToString(textScreenData.font)
})
watch(() => textScreenData.text, (n) => {
  textScreenData.lengthTextInByte = (new TextEncoder().encode(n)).length
})

watch(selectedColorType, async (n, o) => {
  if (o === undefined) return
  await TextScreenService.setTextColorType(StringData.stringToColorType(n))

})
watch(() => textScreenData.color, async (n, o) => {
  if (o === undefined) return
  await TextScreenService.setTextColor(n)

})
watch(selectedFont, async (n, o) => {
  if (o === undefined) return
  await TextScreenService.setFont(StringData.stringToFontName(n))
})
watch(() => textScreenData.brightness, async (n, o) => {
  if (o === undefined) return
  TextScreenService.setTextBrightness(n)
})
watch(() => textScreenData.tick, async (n, o) => {
  if (o === undefined) return
  TextScreenService.setTextTick(n)
})
const sendText = async () => {
  if (textScreenData.lengthTextInByte >= 2000)
    return
  await TextScreenService.setText(textScreenData.text)
}
const onMinusPosition = async () => {
  textScreenData.yPosition = (await TextScreenService.setYPosition(textScreenData.yPosition - 1))['newValue']
}
const onPlusPosition = async () => {
  textScreenData.yPosition = (await TextScreenService.setYPosition(textScreenData.yPosition + 1))['newValue']
}
</script>

<template>
  <div class="w-full h-full relative">

    <GroupItem label="Văn bản">
      <div class="relative w-full px-4 py-2 flex">
        <TextInput :label="`Nội dung văn bản (còn lại ${2000 - textScreenData.lengthTextInByte}) :`"
          v-model="textScreenData.text"></TextInput>
        <div @click="() => sendText()" class="h-8 aspect-square my-auto">
          <Send></Send>
        </div>
      </div>
      <div class="w-full h-[1px] bg-dark-500/20"></div>

      <div class="relative w-full px-4">
        <AdjustmentItem @onMinus="onMinusPosition" @onPlus="onPlusPosition">
          <span class="font-normal">Điều chỉnh độ cao: {{ textScreenData.yPosition }}</span>
          <span class="font-light text-sm">
            Bấm vào +/- để lên xuống
          </span>
        </AdjustmentItem>
      </div>
      <div class="w-full h-[1px] bg-dark-500/20 my-2"></div>

      <div class="relative w-full px-4">
        <MenuItem @itemClick="() => showSelectFont = true" label="Chọn font văn bản" detail="Chọn font chữ cho văn bản">
        <template #icon>
          <div class="h-8 aspect-square">
            <Pencil />
          </div>
        </template>
        </MenuItem>
      </div>
      <div class="w-full h-[1px] bg-dark-500/20 my-2"></div>

      <div class="relative w-full px-4">

        <MenuItem @itemClick="() => showSelectColorType = true" label="Chọn hiệu ứng"
          :detail="`Hiệu ứng hiện tại [${selectedColorType}]`">
        <template #icon>
          <div class="h-8 aspect-square">
            <Effect />
          </div>
        </template>
        </MenuItem>
      </div>
      <div class="w-full h-[1px] bg-dark-500/20"></div>

      <Transition name="bounce">
        <div v-if="selectedColorType === StringData.colorTypeToString('ColorType_Static')"
          class=" w-full h-full flex justify-center mb-4">
          <ColorPicker v-model:color="textScreenData.color" />
        </div>
      </Transition>
      <div class="w-full h-[1px] bg-dark-500/20"></div>

      <div class="w-full px-4">

        <SliderItem class="mb-2" :icon="Light" label="Độ sáng văn bản" v-model="textScreenData.brightness" :min="0"
          :max="255" :step="5">
        </SliderItem>
      </div>
      <div class="w-full h-[1px] bg-dark-500/20 my-2"></div>

      <div class="mb-2 px-4">

        <SliderItem :icon="Speed" label="Tốc độ chữ (càng lớn càng chậm)" v-model="textScreenData.tick" :min="0"
          :max="100" :step="10">

        </SliderItem>
      </div>

    </GroupItem>



    <Transition name="bounce">
      <SelectList :closeWhenSelect="true" v-if="showSelectFont" v-model:show="showSelectFont"
        v-model:selected-item="selectedFont" label="Chọn font cho văn bản"
        :list-item='StringData.listFontName.map((font) => ({ text: StringData.fontNameToString(font) }))'>
      </SelectList>
    </Transition>

    <Transition name="bounce">
      <SelectList :closeWhenSelect="true" v-if="showSelectColorType" v-model:show="showSelectColorType"
        v-model:selected-item="selectedColorType" label="Chọn màu"
        :list-item='StringData.listColorTypeName.map((colorType) => ({ text: StringData.colorTypeToString(colorType) }))'>
      </SelectList>
    </Transition>
  </div>
</template>

<style scoped></style>
