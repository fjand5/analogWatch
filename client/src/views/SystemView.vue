<script setup>
import { onMounted, reactive, watch } from "vue";

import { storeToRefs } from "pinia";
import GroupItem from "~/components/base/GroupItem.vue";
import Time from "~/components/icon/Time.vue";
import { useLedStore } from "~/store";
import BaseView from "~/views/BaseView.vue";
import MenuItem from "../components/MenuItem.vue";
import SelectList from "../components/SelectList.vue";
import ToggleItem from "~/components/ToggleItem.vue";

const ledStore = useLedStore();
const { timeStamp, autoSyncTime } = storeToRefs(ledStore);

const showSelectTime = reactive({
  second: undefined,
  minute: undefined,
  hour: undefined,
});
const time = reactive({
  second: undefined,
  minute: undefined,
  hour: undefined,
});
onMounted(async () => {
  await ledStore.getLed();

  const date = new Date(timeStamp.value * 1000 - 7 * 60 * 60 * 1000);
  time.hour = date.getHours();
  time.minute = date.getMinutes();
  time.second = date.getSeconds();
});
watch(time, async (o, n) => {
  const date = new Date(timeStamp.value * 1000 - 7 * 60 * 60 * 1000);
  date.setSeconds(time.second);
  date.setMinutes(time.minute);
  date.setHours(time.hour);
  await ledStore.setDateTime(date.getTime() / 1000);
});
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Hệ thống">
      <GroupItem label="Cài Đặt Thời Gian">
        <div class="relative w-full px-4">
          <MenuItem
            @itemClick="
              () => {
                showSelectTime.hour = true;
              }
            "
            :label="`Cài giờ [${time.hour}]`"
          >
            <template #icon>
              <div class="h-8 aspect-square">
                <Time></Time>
              </div>
            </template>
          </MenuItem>
          <MenuItem
            @itemClick="
              () => {
                showSelectTime.minute = true;
              }
            "
            :label="`Cài phút [${time.minute}]`"
          >
            <template #icon>
              <div class="h-8 aspect-square">
                <Time></Time>
              </div>
            </template>
          </MenuItem>
          <MenuItem
            @itemClick="
              () => {
                showSelectTime.second = true;
              }
            "
            :label="`Cài giây [${time.second}]`"
          >
            <template #icon>
              <div class="h-8 aspect-square">
                <Time></Time>
              </div>
            </template>
          </MenuItem>
        </div>
      </GroupItem>
      <GroupItem label="Đồng bộ thời gian">
        <div class="flex items-center w-full px-4">
          <span class="shrink-0">{{`${autoSyncTime?'Đang tự ':'Không'} cập nhật thời gian`}}</span>
          <ToggleItem
            :model-value="autoSyncTime"
            v-on:update:model-value="
              async (v) => await ledStore.setAutoSyncTime(v)
            "
          ></ToggleItem>
        </div>
      </GroupItem>
    </BaseView>
    <Transition name="bounce">
      <SelectList
        v-if="showSelectTime.hour"
        :closeWhenSelect="true"
        v-model:show="showSelectTime.hour"
        v-model:selected-item="time.hour"
        @onSelected="(item) => (time.hour = item.text)"
        label="Chọn giờ"
        :list-item="
          Array.from(Array(24).keys()).map((n) => ({
            text: n,
            label: n,
          }))
        "
      >
      </SelectList>
    </Transition>
    <Transition name="bounce">
      <SelectList
        v-if="showSelectTime.minute"
        :closeWhenSelect="true"
        v-model:show="showSelectTime.minute"
        v-model:selected-item="time.minute"
        @onSelected="(item) => (time.minute = item.text)"
        label="Chọn phút"
        :list-item="
          Array.from(Array(60).keys()).map((n) => ({
            text: n,
            label: n,
          }))
        "
      >
      </SelectList>
    </Transition>
    <Transition name="bounce">
      <SelectList
        v-if="showSelectTime.second"
        :closeWhenSelect="true"
        v-model:show="showSelectTime.second"
        v-model:selected-item="time.second"
        @onSelected="(item) => (time.second = item.text)"
        label="Chọn giây"
        :list-item="
          Array.from(Array(60).keys()).map((n) => ({
            text: n,
            label: n,
          }))
        "
      >
      </SelectList>
    </Transition>
  </div>
</template>

<style scoped></style>
