<script setup>
import { RouterLink } from "vue-router";
import { onMounted, ref } from "vue";
import BaseView from "~/views/BaseView.vue";
import LoadingLine from "~/components/LoadingLine.vue";
import Wifi from "~/components/icon/Wifi.vue";
import Plus from "~/components/icon/Plus.vue";
import Refesh from "~/components/icon/Refesh.vue";
import { wifiUtlis } from "~/utlis";
import Signal from "~/components/icon/Signal.vue";
import GroupItem from "~/components/base/GroupItem.vue";
import WifiItem from "~/components/WifiItem.vue";
import MenuItem from "~/components/MenuItem.vue";
import { useWifiStore } from "~/store";
import { storeToRefs } from "pinia";
const currentWifi = ref(null);

const wifiStore = useWifiStore();
const { nearWifi, STASSID, STAPSK, APSSID, APPSK,ip } = storeToRefs(wifiStore);
onMounted(async () => {
  currentWifi.value = await wifiStore.getWifi();
  await wifiStore.scanWifi();
});
const refesh = async () => {
  await wifiStore.scanWifi();
};
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Thiết lập Wifi">
      <template #rightIcon>
        <div
          @click="refesh"
          v-if="nearWifi.length"
          class="h-full aspect-square"
        >
          <Refesh />
        </div>
      </template>
      <GroupItem
        label="Mạng đã lưu"
        :listItem="[
          {
            name: 'setWifi',
            isStation: true,
            id: currentWifi?.ApSSID ? currentWifi.ApSSID : '',
            pass: currentWifi?.ApPASS ? currentWifi.ApPASS : '',
            detail: 'Tên wifi và mật khẩu của đồng hồ phát ra',
            icon: Signal,
          },
          {
            name: 'setWifi',
            isStation: false,
            id: STASSID,
            pass: STAPSK,
            detail: `Đã kết nối, ip: ${ip}`,
            icon: Wifi,
          },
        ]"
      >
        <template #item="{ name, isStation, id, pass, detail, icon }">
          <div class="w-full px-4">
            <RouterLink
              :to="{
                name,
                force: true,
                state: {
                  isStation,
                  id,
                  pass,
                },
              }"
            >
              <MenuItem :label="id" :detail="detail">
                <template #icon>
                  <div class="h-8 aspect-square">
                    <component :is="icon"></component>
                  </div>
                </template>
              </MenuItem>
            </RouterLink>
          </div>
        </template>
      </GroupItem>
      <div v-if="!nearWifi.length" class="w-full h-fit my-2">
        <LoadingLine></LoadingLine>
      </div>
      <div v-else>
        <GroupItem label="Mạng xung quanh" :listItem="nearWifi">
          <template #item="{ ssid, rssi }">
            <div class="w-full px-4">
              <RouterLink
                :to="{
                  name: 'setWifi',
                  force: true,
                  state: { id: ssid },
                }"
              >
                <div class="w-full h-full">
                  <WifiItem :ssid="ssid" :rssi="rssi"></WifiItem>
                </div>
              </RouterLink>
            </div>
          </template>
        </GroupItem>
        <div class="w-full px-4 -mt-10 mb-4">
          <RouterLink
            :to="{
              name: 'setWifi',
              force: true,
              state: { ssid: undefined },
            }"
          >
            <div class="w-full h-full">
              <MenuItem label="Thêm mạng" detail="Nhập thủ công">
                <template #icon>
                  <div class="h-8 aspect-square">
                    <Plus />
                  </div>
                </template>
              </MenuItem>
            </div>
          </RouterLink>
        </div>
      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
