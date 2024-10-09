<script setup>
const props = defineProps(['listItem', 'label'])

</script>

<template>
  <div class="flex flex-col gap-2 mb-14">
    <div v-if="label" class="px-4">
      <span class="text-dark-500/70  uppercase">
        {{ label }}
      </span>
    </div>
    <div class="w-full h-fit bg-dark-200/20  flex flex-col border-t border-b border-dark-500/20">

      <template v-if="props?.listItem" v-for="(item, index) in props.listItem">
        <slot name="item" v-bind="item"></slot>
        <div v-if="index < props.listItem.length - 1" class="w-full h-fit px-4">
          <div class="w-full h-[1px] bg-dark-500/20"></div>
        </div>

      </template>
      <template v-else>
        <slot></slot>
      </template>
    </div>
  </div>
</template>

<style scoped></style>
