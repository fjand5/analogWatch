<script setup>
import Eye from "~/components/icon/Eye.vue";
import MenuItem from "~/components/MenuItem.vue";
import BaseView from "./BaseView.vue";
import SliderItem from "../components/SliderItem.vue";
import Light from "../components/icon/Light.vue";
import { onMounted, reactive, ref, watch } from "vue";
import Content from "../components/icon/Content.vue";
import { useLedStore } from "~/store";
import { storeToRefs } from "pinia";
import ColorPicker from "~/components/ColorPicker.vue";
import Color from "~/components/icon/Color.vue";

const ledStore = useLedStore();
const { brightness, secondHandColor, minuteHandColor, hourHandColor } =
  storeToRefs(ledStore);

const handColor = reactive({
  second: undefined,
  minute: undefined,
  hour: undefined,
});
const showSelectColor = reactive({
  second: undefined,
  minute: undefined,
  hour: undefined,
});
onMounted(async () => {
  await ledStore.getLed();
  handColor.second = secondHandColor;
  handColor.minute = minuteHandColor;
  handColor.hour = hourHandColor;
});
watch(brightness, async (n, o) => {
  if (o === undefined) return;
  await ledStore.setBrightness(n);
});
watch(
  () => handColor.second,
  async (n, o) => {
    if (o === undefined) return;
    ledStore.setSecondHandColor(n);
  }
);
watch(
  () => handColor.minute,
  async (n, o) => {
    if (o === undefined) return;
    ledStore.setMinuteHandColor(n);
  }
);
watch(
  () => handColor.hour,
  async (n, o) => {
    if (o === undefined) return;
    ledStore.setHourHandColor(n);
  }
);
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Hiển thị">
      <div class="relative w-full px-4">
        <SliderItem
          :icon="Light"
          label="Độ sáng"
          v-model="brightness"
          :min="0"
          :max="255"
          :step="5"
        >
        </SliderItem>
      </div>

      <div class="relative w-full px-4">
        <MenuItem
          label="Màu Kim Giây"
          detail="Cài đặt màu kim giây"
          @click="
            () => {
              showSelectColor.second = !showSelectColor.second;
              showSelectColor.minute = false;
              showSelectColor.hour = false;
            }
          "
        >
          <template #icon>
            <div class="h-8 aspect-square rounded-md">
              <Color></Color>
            </div>
          </template>
        </MenuItem>

        <Transition name="bounce">
          <div
            v-if="showSelectColor.second == true"
            class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
          >
            <ColorPicker v-model:color="handColor.second" />
          </div>
        </Transition>
      </div>
      <div class="relative w-full px-4">
        <MenuItem
          label="Màu Kim Phút"
          detail="Cài đặt màu kim phút"
          @click="
            () => {
              showSelectColor.second = false;
              showSelectColor.minute = !showSelectColor.minute;
              showSelectColor.hour = false;
            }
          "
        >
          <template #icon>
            <div class="h-8 aspect-square rounded-md">
              <Color></Color>
            </div>
          </template>
        </MenuItem>

        <Transition name="bounce">
          <div
            v-if="showSelectColor.minute == true"
            class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
          >
            <ColorPicker v-model:color="handColor.minute" />
          </div>
        </Transition>
      </div>
      <div class="relative w-full px-4">
        <MenuItem
          label="Màu Kim Giờ"
          detail="Cài đặt màu kim giờ"
          @click="
            () => {
              showSelectColor.second = false;
              showSelectColor.minute = false;
              showSelectColor.hour = !showSelectColor.hour;
            }
          "
        >
          <template #icon>
            <div class="h-8 aspect-square rounded-md">
              <Color></Color>
            </div>
          </template>
        </MenuItem>

        <Transition name="bounce">
          <div
            v-if="showSelectColor.hour == true"
            class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
          >
            <ColorPicker v-model:color="handColor.hour" />
          </div>
        </Transition>
      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
