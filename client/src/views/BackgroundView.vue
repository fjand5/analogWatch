<script setup>
import { onMounted, reactive, ref, watch } from 'vue';
import GroupItem from '~/components/base/GroupItem.vue';
import ColorPicker from '~/components/ColorPicker.vue';
import Color from '~/components/icon/Color.vue';
import Effect from '~/components/icon/Effect.vue';
import Light from '~/components/icon/Light.vue';
import Send from '~/components/icon/Send.vue';
import Speed from '~/components/icon/Speed.vue';
import MenuItem from '~/components/MenuItem.vue';
import SelectList from '~/components/SelectList.vue';
import SliderItem from '~/components/SliderItem.vue';
import TextInput from '~/components/TextInput.vue';
import { BackgroundService } from '~/services';
import { StringData } from '~/utlis';
import BaseView from './BaseView.vue';

const showSelectEffect = ref(false)
const selectedEffect = ref({
  text:'',
  label:''
})

const selectedColorType = ref({
  text:'',
  label:''
})
const showSelectColorType = ref(false)
const backgroundData = reactive({
  speed: undefined,
  brightness: undefined,
  effect: undefined,
  colorType: undefined,
  text: '',
  color: '#0000',
  

})
onMounted(async () => {
  const result = await BackgroundService.getBackground()
  backgroundData.brightness = result['brightness']
  backgroundData.effect = result['effect']
  backgroundData.text = result['text']
  backgroundData.speed = result['tick']
  backgroundData.colorType = result['colorType']
  backgroundData.color = result['color']

  selectedEffect.value.text = StringData.backgroundEffectToString(backgroundData.effect)
  selectedColorType.value.text = StringData.colorTypeToString(backgroundData.colorType)
})

watch(() => backgroundData.brightness, async (n, o) => {
  if (o === undefined) return

  await BackgroundService.setBackgroundBrightness(n)

})
watch(() => backgroundData.speed, async (n, o) => {
  if (o === undefined) return

  await BackgroundService.setBackgroundTick(n)

})
watch(() => backgroundData.color, async (n, o) => {
  if (o === undefined) return
  await BackgroundService.setBackgroudColor(n)

})
watch(selectedEffect, async (n, o) => {
  if (o === undefined) return
  await BackgroundService.setBackgroundEffect(StringData.stringToBackgroudEffectName(n.text))

})
watch(selectedColorType, async (n, o) => {
  if (o === undefined) return
  await BackgroundService.setBackgroudColorType(StringData.stringToColorType(n.text))

})
const sendText = async () => {
  await BackgroundService.setText(backgroundData.text)

}
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Cài đặt nền">
      <GroupItem label="Độ sáng, tốc độ">
        <div class="relative w-full px-4 ">

          <SliderItem class="mb-2" :icon="Light" label="Độ sáng nền" v-model="backgroundData.brightness" :min="0"
            :max="230" :step="5">
          </SliderItem>
          <div>

            <div class="w-full h-[1px] bg-dark-500/20"></div>
            <SliderItem class="mb-2" :icon="Speed" label="Tốc độ (càng lớn càng chậm)" v-model="backgroundData.speed"
              :min="0" :max="100" :step="10">
            </SliderItem>
          </div>

        </div>
      </GroupItem>
      <GroupItem label="Màu, hiệu ứng">
        <div class="relative w-full px-4 ">
          <MenuItem @itemClick="() => showSelectEffect = true" label="Chọn hiệu ứng"
            :detail="`Hiệu ứng hiện tại [${selectedEffect?.text || ''}]`">
          <template #icon>
            <div class="h-8 aspect-square">
              <Effect />
            </div>
          </template>
          </MenuItem>
          <div class="w-full h-[1px] bg-dark-500/20"></div>
          <Transition name="bounce">


            <div
              v-if="showSelectEffect == false && selectedEffect.text === StringData.backgroundEffectToString('BackgroundEffect_RunText')"
              class="relative w-full px-4 py-2 flex">
              <TextInput label="Nội dung chữ chạy:" v-model="backgroundData.text"></TextInput>
              <div @click="() => sendText()" class="h-8 aspect-square my-auto">
                <Send></Send>
              </div>
            </div>
          </Transition>
          <div class="w-full h-[1px] bg-dark-500/20"></div>

          <MenuItem @itemClick="() => showSelectColorType = true" label="Chọn màu"
            :detail="`Màu hiện tại [${selectedColorType?.text || ''}]`">
          <template #icon>
            <div class="h-8 aspect-square">
              <Color />
            </div>
          </template>
          </MenuItem>

          <Transition name="bounce">
            <div
              v-if="showSelectColorType == false && selectedColorType.text === StringData.colorTypeToString('ColorType_Static')"
              class=" w-full h-full flex justify-center mb-4">
              <ColorPicker v-model:color="backgroundData.color" />
            </div>
          </Transition>
        </div>
      </GroupItem>


      <Transition name="bounce">
        <SelectList :closeWhenSelect="true" v-if="showSelectEffect" v-model:show="showSelectEffect" v-model:selected-item="selectedEffect"
          label="Chọn hiệu ứng"
          :list-item='StringData.listBackgroundEffectName.map((effect) => ({ text: StringData.backgroundEffectToString(effect) }))'>
        </SelectList>
      </Transition>
      <Transition name="bounce">
        <SelectList :closeWhenSelect="true" v-if="showSelectColorType" v-model:show="showSelectColorType"
          v-model:selected-item="selectedColorType" label="Chọn màu"
          :list-item='StringData.listColorTypeName.map((colorType) => ({ text: StringData.colorTypeToString(colorType) }))'>
        </SelectList>

      </Transition>


    </BaseView>

  </div>
</template>

<style scoped></style>
