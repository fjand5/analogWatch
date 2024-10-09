<script setup>
import { wifiUtlis } from '~/utlis';
import MenuItem from './menuItem.vue';
import Wifi from './icon/Wifi.vue';
const {ssid,rssi} = defineProps(['ssid','rssi'])
</script>

<template>
  <MenuItem :label="ssid">
  <template #icon>
    <div class="h-8 aspect-square" :style="{
      opacity: wifiUtlis.rssiToPercent(rssi) + '%'
    }">
      <Wifi />
    </div>
  </template>
  </MenuItem>
</template>

<style scoped></style>
