<script setup>
import { reactive, ref, watch } from 'vue';
import ControlItem from './ControlItem.vue';
import Toggle from './Toggle.vue';
import Plus from './icon/Plus.vue';
import Minus from './icon/Minus.vue';
const props = defineProps(['disableMinus', 'disablePlus'])
const emit = defineEmits(['onMinus', 'onPlus'])

const animate = reactive({
  minus: false,
  plus: false
})
</script>

<template>
  <ControlItem>
    <template #content>
      <div class="flex justify-between items-center w-full">

        <div class="flex flex-col justify-between ">
          <slot></slot>
        </div>
        <div class="flex gap-6">
          <div @click="() => {
            emit('onMinus')
            animate.minus = false
          }" @mousedown="() => animate.minus = true" @touchstart="() => animate.minus = true"
            @touchend="() => animate.minus = false" @touchcancel="() => animate.minus = false"
            class="h-9 p-1 aspect-square rounded-full border bodder-dark-500 transition-all"
            :class="{ 'scale-75': animate.minus, 'border-dark-500/40 text-dark-500/40 pointer-events-none':props.disableMinus}">
            <Minus></Minus>
          </div>
          <div @click="() => {
            emit('onPlus')
            animate.plus = false
          }" @mousedown="() => animate.plus = true" @touchstart="() => animate.plus = true"
            @touchend="() => animate.plus = false" @touchcancel="() => animate.plus = false"
            
            :class="{ 'scale-75': animate.plus, 'border-dark-500/40 text-dark-500/40 pointer-events-none':props.disablePlus}"
            
            class="h-9 p-1 aspect-square rounded-full border border-dark-500 transition-all">

            <Plus></Plus>
          </div>
        </div>
      </div>
    </template>
  </ControlItem>
</template>

<style scoped></style>
