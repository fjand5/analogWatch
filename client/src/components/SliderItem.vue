<script setup>
import { wifiUtlis } from '~/utlis';
import MenuItem from './menuItem.vue';
import Wifi from './icon/Wifi.vue';
import ControlItem from './ControlItem.vue';
import Toggle from './Toggle.vue';
import { onMounted, ref, watch } from 'vue';
import Light from './icon/Light.vue';
import Slider from './Slider.vue';
const props = defineProps(['modelValue', 'icon', 'label', 'min', 'max', 'step'])
const emit = defineEmits(['update:modelValue'])
const value = ref()
const timerId = ref()
onMounted(() => {
  value.value = props.modelValue

})
watch(() => props.modelValue, (n, o) => {
  if (o == undefined)
    value.value = n
})
watch(value, (n) => {
  clearTimeout(timerId.value)
  timerId.value = setTimeout(() => { emit('update:modelValue', n) }, 250)


})
</script>

<template>
  <ControlItem>
    <template #icon>
      <div class="h-8 aspect-square">
        <component :is="props.icon"></component>
      </div>
    </template>
    <template #content>
      <div>
        <Slider v-model="value" :label="`${props.label}: ${value}`" :min="props.min" :max="props.max" :step="props.step">
        </Slider>
      </div>
    </template>
  </ControlItem>
</template>

<style scoped></style>
