<script setup>

import { storeToRefs } from "pinia";
import { onMounted, ref } from "vue";
import { RouterLink } from "vue-router";
import Eye from "~/components/icon/Eye.vue";
import Power from "~/components/icon/Power.vue";
import Wifi from "~/components/icon/Wifi.vue";
import MenuItem from "~/components/MenuItem.vue";
import { useLedStore } from "~/store";
import System from "../components/icon/System.vue";
import BaseView from "./BaseView.vue";

const controlBarRef = ref(null);
const systemData = ref();
const ledStore = useLedStore();
const { power } = storeToRefs(ledStore);

onMounted(async () => {
  await ledStore.getLed();
});

const togglePower = async () => {
  await ledStore.togglePower();
};
const homeScroll = (e) => {
  const target = e.target;
  if (target.scrollTop > 115) {
    controlBarRef.value.style.top = target.scrollTop - 115 + "px";
  } else if (target.scrollTop == 0) {
    // trường hợp cuộn nhanh quá, không qua mốc 115 sẽ gặp lỗi
    controlBarRef.value.style.top = 0;
  }
};
</script>

<template>
  <div class="w-full h-full">
    <BaseView @onScroll="homeScroll" label="Cài đặt">
      <div class="w-full h-full flex flex-col relative px-4">
        <div class="relative flex flex-col gap-6 mb-8 z-10">
          <div ref="controlBarRef" class="relative py-4">
            <div
              class="absolute w-full h-8 bg-dark-100/50 backdrop-blur-sm top-0"
            ></div>
            <div
            @click="togglePower"

              :class="power ? 'border-dark-300' : 'border-dark-200'"
              class="border w-full h-14 rounded-full flex backdrop-blur bg-dark-200/20 justify-center gap-16 items-center px-3 transition-all"
            >
              <div
                class="h-8 aspect-square transition-all"
                :class="
                  power
                    ? 'stroke-dark-300 drop-shadow-[0_0px_5px_theme(colors.dark.300)]'
                    : 'stroke-dark-500/60'
                "
              >
                <Power></Power>
              </div>
            </div>
          </div>
        </div>
        <div class="relative w-full">
          <RouterLink
            :to="{
              name: 'display',
            }"
          >
            <MenuItem label="Hiển thị" detail="Cài màu sắc, độ sáng các kim">
              <template #icon>
                <div class="h-8 aspect-square">
                  <Eye />
                </div>
              </template>
            </MenuItem>
          </RouterLink>
          <RouterLink to="/wifi">
            <MenuItem
              label="Mạng và Internet"
              detail="Kết nối Wi-Fi, điểm phát sóng"
            >
              <template #icon>
                <div class="h-8 aspect-square">
                  <Wifi />
                </div>
              </template>
            </MenuItem>
          </RouterLink>
          <RouterLink
            :to="{
              name: 'system',
              force: true,
              state: { params: { systemData: JSON.stringify(systemData) } },
            }"
          >
            <MenuItem
              label="Hệ thống"
              detail="Cài đặt thời gian"
            >
              <template #icon>
                <div class="h-8 aspect-square">
                  <System />
                </div>
              </template>
            </MenuItem>
          </RouterLink>
        </div>
      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
