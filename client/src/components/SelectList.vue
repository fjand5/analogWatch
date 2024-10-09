<script setup>
import Modal from '~/components/base/Modal.vue';
import SelectCircle from '~/components/icon/SelectCircle.vue';
import Close from './icon/Close.vue';
const props = defineProps(['label', 'listItem', 'show', 'selectedItem'])
const emit = defineEmits(['update:selectedItem', 'update:show', 'onSelected'])

const itemSelect = (item) => {
  if (props.selectedItem)
    emit('update:selectedItem', item)
  emit('onSelected', item)
}
const close = () => {
  emit('update:show', false)
}
</script>

<template>
  <Modal>
    <div class="w-full h-full bg-dark-100 rounded-lg shadow-xl">
      <div class="w-full h-full flex flex-col">
        <div class="p-5 flex items-center">
          <span class="font-medium text-3xl">
            {{ label }}
          </span>
          <div @click="close" class="ml-auto h-full w-6">

            <Close></Close>
          </div>
        </div>
        <div class="w-full h-[1px] shrink-0 bg-dark-400"></div>
        <div class="w-full flex-1 overflow-auto p-4">
          <div class="w-full h-full  overflow-y-scroll no-scrollbar appearance-none bg-inherit flex flex-col gap-2">
            <template v-for="item in listItem">
              <div @click="() => itemSelect(item)" :class="item.class"
                class="flex gap-6 items-center w-full h-8 cursor-pointer">
                <div v-if="selectedItem != undefined" class="h-full aspect-square p-1">
                  <SelectCircle :selected="selectedItem == item.text"></SelectCircle>
                </div>
                <span class="font-normal text-lg">
                  {{ item.text }}
                </span>
              </div>
              <div class="w-full h-[1px] bg-dark-500/20"></div>

            </template>
          </div>
        </div>
      </div>
    </div>
  </Modal>
</template>

<style scoped></style>
