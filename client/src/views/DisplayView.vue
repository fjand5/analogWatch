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
import GroupItem from "~/components/base/GroupItem.vue";
import Time from "~/components/icon/Time.vue";
import Slider from "~/components/Slider.vue";

const ledStore = useLedStore();
const {
  brightness,
  secondHandColor,
  minuteHandColor,
  hourHandColor,
  timeColor,
  dayColor,
  lunarDayColor,
  timeShowTime,
  dayShowTime,
  lunarDayShowTime
} = storeToRefs(ledStore);

const handColor = reactive({
  second: undefined,
  minute: undefined,
  hour: undefined,
  time: undefined,
  day: undefined,
  lunarDay: undefined,
});
const showSelectColor = reactive({
  second: undefined,
  minute: undefined,
  hour: undefined,
  time: undefined,
  day: undefined,
  lunarDay: undefined,
});
const showSelectTime = reactive({
  time: undefined,
  day: undefined,
  lunarDay: undefined,
});
onMounted(async () => {
  await ledStore.getLed();
  handColor.second = secondHandColor;
  handColor.minute = minuteHandColor;
  handColor.hour = hourHandColor;

  handColor.time = timeColor;
  handColor.day = dayColor;
  handColor.lunarDay = lunarDayColor;
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
      <div class="relative w-full px-4 mb-10">
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
      <GroupItem label="Cài Đặt Đồng Hồ Kim">
        <div class="relative w-full px-4">
          <MenuItem
            label="Màu Kim Giây"
            detail="Cài đặt màu kim giây"
            @click="
              () => {
                showSelectColor.second = !showSelectColor.second;
                showSelectColor.minute = false;
                showSelectColor.hour = false;
                showSelectColor.time = false;
                showSelectColor.day = false;
                showSelectColor.lunarDay = false;
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
              <ColorPicker
                :color="handColor.second"
                @update:color="
                  async (color) => {
                    await ledStore.setSecondHandColor(color);
                  }
                "
              />
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
                showSelectColor.time = false;
                showSelectColor.day = false;
                showSelectColor.lunarDay = false;
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
              <ColorPicker
                :color="handColor.minute"
                @update:color="
                  async (color) => {
                    await ledStore.setMinuteHandColor(color);
                  }
                "
              />
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
                showSelectColor.time = false;
                showSelectColor.day = false;
                showSelectColor.lunarDay = false;
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
              <ColorPicker
                :color="handColor.hour"
                @update:color="
                  async (color) => {
                    await ledStore.setHourHandColor(color);
                  }
                "
              />
            </div>
          </Transition>
        </div>
      </GroupItem>
      <GroupItem label="Cài Đặt Màu Đồng Hồ Số">
        <div class="relative w-full px-4">
          <MenuItem
            label="Màu Giờ Phút Giây"
            detail="Cài đặt màu đồng hồ"
            @click="
              () => {
                showSelectColor.second = false;
                showSelectColor.minute = false;
                showSelectColor.hour = false;
                showSelectColor.time = !showSelectColor.time;
                showSelectColor.day = false;
                showSelectColor.lunarDay = false;
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
              v-if="showSelectColor.time == true"
              class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
            >
              <ColorPicker
                :color="handColor.time"
                @update:color="
                  async (color) => {
                    await ledStore.setTimeColor(color);
                  }
                "
              />
            </div>
          </Transition>
        </div>
        <div class="relative w-full px-4">
          <MenuItem
            label="Màu Ngày Tháng Dương Lịch"
            detail="Cài đặt màu dương lịch"
            @click="
              () => {
                showSelectColor.second = false;
                showSelectColor.minute = false;
                showSelectColor.hour = false;
                showSelectColor.time = false;
                showSelectColor.day = !showSelectColor.day;
                showSelectColor.lunarDay = false;
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
              v-if="showSelectColor.day == true"
              class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
            >
              <ColorPicker
                :color="handColor.day"
                @update:color="
                  async (color) => {
                    await ledStore.setDayColor(color);
                  }
                "
              />
            </div>
          </Transition>
        </div>
        <div class="relative w-full px-4">
          <MenuItem
            label="Màu Ngày Tháng Âm Lịch"
            detail="Cài đặt màu âm lịch"
            @click="
              () => {
                showSelectColor.second = false;
                showSelectColor.minute = false;
                showSelectColor.hour = false;
                showSelectColor.time = false;
                showSelectColor.day = false;
                showSelectColor.lunarDay = !showSelectColor.lunarDay;
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
              v-if="showSelectColor.lunarDay == true"
              class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
            >
              <ColorPicker
                :color="handColor.lunarDay"
                @update:color="
                  async (color) => {
                    await ledStore.setLunarDayColor(color);
                  }
                "
              />
            </div>
          </Transition>
        </div>
      </GroupItem>
      <GroupItem label="Cài Đặt Thời Gian Đồng Hồ Số">
        <div class="relative w-full px-4">
          <MenuItem
            label="Thời Gian Hiển Thị Giờ Phút Giây"
            detail="Cài gian hiển thị giờ phút giây"
            @click="
              () => {
                showSelectTime.time = !showSelectTime.time;
                showSelectTime.day = false;
                showSelectTime.lunarDay = false;
              }
            "
          >
            <template #icon>
              <div class="h-8 aspect-square rounded-md">
                <Time></Time>
              </div>
            </template>
          </MenuItem>

          <Transition name="bounce">
            <div
              v-if="showSelectTime.time == true"
              class="w-full h-full flex justify-center items-center mb-4 p-2 rounded-md"
            >
              <Slider
                :label="`${timeShowTime} giây`"
                :min="3"
                :max="60"
                :step="1"
                :model-value="timeShowTime"
                @update:model-value="
                  async (v) => {
                    await ledStore.setTimeShowTime(v);
                  }
                "
              ></Slider>
            </div>
          </Transition>
        </div>
        <div class="relative w-full px-4">
          <MenuItem
            label="Thời Gian Hiển Thị Dương Lịch"
            detail="Cài gian hiển thị ngày tháng dương lịch"
            @click="
              () => {
                showSelectTime.time = false;
                showSelectTime.day = !showSelectTime.day;
                showSelectTime.lunarDay = false;
              }
            "
          >
            <template #icon>
              <div class="h-8 aspect-square rounded-md">
                <Time></Time>
              </div>
            </template>
          </MenuItem>

          <Transition name="bounce">
            <div
              v-if="showSelectTime.day == true"
              class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
            >
              <Slider
                :label="`${dayShowTime} giây`"
                :min="3"
                :max="60"
                :step="1"
                :model-value="dayShowTime"
                @update:model-value="
                  async (v) => {
                    await ledStore.setDayShowTime(v);
                  }
                "
              ></Slider>
            </div>
          </Transition>
        </div>
        <div class="relative w-full px-4">
          <MenuItem
            label="Thời Gian Hiển Thị Âm Lịch"
            detail="Cài thời gian hiển thị ngày tháng âm lịch"
            @click="
              () => {
                showSelectTime.time = false;
                showSelectTime.day = false;
                showSelectTime.lunarDay = !showSelectTime.lunarDay;
              }
            "
          >
            <template #icon>
              <div class="h-8 aspect-square rounded-md">
                <Time></Time>
              </div>
            </template>
          </MenuItem>

          <Transition name="bounce">
            <div
              v-if="showSelectTime.lunarDay == true"
              class="w-full h-full flex justify-center items-center mb-4 border border-white p-2 rounded-md"
            >
              <Slider
                :label="`${lunarDayShowTime} giây`"
                :min="3"
                :max="60"
                :step="1"
                :model-value="lunarDayShowTime"
                @update:model-value="
                  async (v) => {
                    await ledStore.setLunarDayShowTime(v);
                  }
                "
              ></Slider>
            </div>
          </Transition>
        </div>
      </GroupItem>
    </BaseView>
  </div>
</template>

<style scoped></style>
