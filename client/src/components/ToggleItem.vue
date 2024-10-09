<script setup>
import { onMounted, ref, watch } from "vue";
import ControlItem from "./ControlItem.vue";
import Toggle from "./Toggle.vue";
const props = defineProps(["modelValue"]);
const emit = defineEmits(["update:modelValue"]);
const toggle = ref();
onMounted(() => {
  toggle.value = props.modelValue;
});
watch(
  () => props.modelValue,
  (n, o) => {
    toggle.value = n;
  }
);
watch(toggle, (n) => {
  emit("update:modelValue", n);
});
</script>

<template>
  <ControlItem>
    <template #content>
      <div class="flex justify-between items-center w-full">
        <div class="flex flex-col justify-between">
          <slot></slot>
        </div>
        <div>
          <Toggle v-model="toggle"></Toggle>
        </div>
      </div>
    </template>
  </ControlItem>
</template>

<style scoped></style>
