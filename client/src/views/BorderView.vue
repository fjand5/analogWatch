<script setup>
import MenuItem from '~/components/MenuItem.vue';
import BaseView from './BaseView.vue';
import Speed from '~/components/icon/Speed.vue';
import Color from '~/components/icon/Color.vue';
import { onMounted, reactive, ref, watch } from 'vue';
import { BorderService } from '~/services';
import AdjustmentItem from '~/components/AdjustmentItem.vue';
import GroupItem from '~/components/base/GroupItem.vue';
import SliderItem from '~/components/SliderItem.vue';
import SelectList from '~/components/SelectList.vue';
import { StringData } from '~/utlis';

const showSelectPalette = ref(false)
const selectedPalette = ref(undefined)
const borderData = reactive({
  width: 1,
  tick: undefined,
  palette: undefined
})
onMounted(async () => {
  const result = await BorderService.getBorder()
  borderData.width = result['width']
  borderData.tick = result['tick']
  borderData.palette = result['palette']

  selectedPalette.value = StringData.paletteNameToString(borderData.palette)
})

watch(() => borderData.palette, async (n, o) => {
  if (o === undefined) return
  selectedPalette.value = StringData.paletteNameToString(n)
})
watch(() => borderData.tick, async (n, o) => {
  if (o === undefined) return

  await BorderService.setBorderTick(n)

})
const onSelectedPalette = async (palette) => {
  await BorderService.setBorderPalette(StringData.stringToPaletteName(palette.text))

}
const onMinusWidth = async () => {
  borderData.width = (await BorderService.setBorderWidth(borderData.width - 1))['newValue']
}
const onPlusWidth = async () => {
  borderData.width = (await BorderService.setBorderWidth(borderData.width + 1))['newValue']
}
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Cài đặt viền">

      <GroupItem label="Độ rộng viền">
        <div class="relative w-full px-4">
          <AdjustmentItem :disableMinus="borderData.width <= 0" :disablePlus="borderData.width >= 5"
            @onMinus="onMinusWidth" @onPlus="onPlusWidth">
            <span class="font-normal">Cài đặt độ rộng viền: {{ borderData.width }}</span>
            <span class="font-light text-sm">
              Bấm vào +/- để tăng giảm
            </span>
          </AdjustmentItem>
        </div>
      </GroupItem>
      <Transition name="fade">

        <GroupItem v-if="borderData.width > 0" label="Tốc độ viền">
          <div class="relative w-full px-4">

            <SliderItem :icon="Speed" label="Tốc độ viền (càng lớn càng chậm)" v-model="borderData.tick" :min="0"
              :max="100" :step="10">

            </SliderItem>
            <div class="w-full h-[1px] bg-dark-500/20 my-2"></div>

            <MenuItem @itemClick="() => showSelectPalette = true" label="Chọn màu" detail="Chọn màu từ danh sách">
            <template #icon>
              <div class="h-8 aspect-square">
                <Color />
              </div>
            </template>
            </MenuItem>
          </div>
        </GroupItem>
      </Transition>

      <Transition name="bounce">
        <SelectList v-if="showSelectPalette" v-model:show="showSelectPalette" 
        
          @onSelected="onSelectedPalette"
          label="Chọn màu"
          :list-item='StringData.listPaletteName.map((palette) => ({ text: StringData.paletteNameToString(palette), class: StringData.paletteNameToClass(palette) }))'>
        </SelectList>
      </Transition>
    </BaseView>

  </div>
</template>

<style scoped></style>
