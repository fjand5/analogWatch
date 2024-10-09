<script setup>
import { onMounted, ref } from "vue";
import BaseView from "~/views/BaseView.vue";
import PasswordInput from "~/components/PasswordInput.vue";
import { WifiService } from "~/services";
import { useRouter } from "vue-router";
import TextInput from "~/components/TextInput.vue";
import { useWifiStore } from "~/store";
import { storeToRefs } from "pinia";
const router = useRouter();
const wifiName = ref(null);
const wifiPassword = ref(null);
const isStation = ref(false); // true: esp là trạm phát

const wifiStore = useWifiStore();
const { APSSID, APPSK, STASSID, STAPSK } = storeToRefs(wifiStore);

const hasError = ref(false);
onMounted(async () => {
  await wifiStore.getWifi();
  isStation.value = window.history.state.isStation;

  if (isStation.value) {
    wifiName.value = APSSID.value;
    wifiPassword.value = APPSK.value;
  } else {
    wifiName.value = window.history.state.id;
    wifiPassword.value = window.history.state.pass;
  }
});
const commit = async () => {
  try {
    if (isStation.value) {
      await wifiStore.setWifi({
        apSSID: wifiName.value,
        apPSK: wifiPassword.value,
      });
    } else {
      await wifiStore.setWifi({
        staSSID: wifiName.value,
        staPSK: wifiPassword.value,
      });
    }
    hasError.value = false;

    router.back();
  } catch (error) {
    hasError.value = true;
  }
};
</script>

<template>
  <div class="w-full h-full">
    <BaseView :label="wifiName || 'Nhập wifi thủ công'">
      <div class="w-full flex flex-col gap-10 px-4">
        <span v-if="hasError" class="text-red-400 text-sm font-light"
          >Thất bại</span
        >
        <TextInput v-model="wifiName" label="Tên mạng"></TextInput>
        <PasswordInput v-model="wifiPassword"></PasswordInput>
        <div class="flex justify-end gap-10 text-dark-400">
          <button class="">HỦY</button>
          <button @click="commit" class="">LƯU</button>
        </div>
      </div>
    </BaseView>
  </div>
</template>

<style scoped></style>
