<script setup>
import { useRouter } from 'vue-router'
import Left from '../components/icon/Left.vue';
import { onMounted, ref } from 'vue';
const emit = defineEmits(['onScroll'])

const router = useRouter()
defineProps({
  label: String
})
const navBarRef = ref(null)
const hideLabel = ref(null)
const isHomePage = ref(undefined)
onMounted (()=>{
  isHomePage.value = router.currentRoute.value.path == "/"
})
const itemsScroll = (e) => {
  const target = e.target
  hideLabel.value = target.scrollTop > 40
  emit('onScroll',e)
}
function prevRoutePath() {
  router.back()
  
}

</script>

<template>
  <div class="w-full h-full relative">
    <div ref="navBarRef"
      class="fixed z-20 top-0 w-full max-w-sm  h-10 px-4 gap-5 flex justify-between items-center "
      :class="hideLabel ? 'backdrop-blur-md backdrop-contrast-50 shadow-lg' : ' bg-inherit'">
      <div v-if="!isHomePage"  @click="prevRoutePath" class="h-6 aspect-square">
        <Left />
      </div>
      <div class="absolute bottom-[50%] right-[50%] translate-x-[50%] translate-y-[50%] font-medium text-lg  transition-all duration-500 mx-auto" :class="hideLabel ? 'opacity-100' : 'opacity-0'">
        {{ label }}
      </div>
      <div class="h-6 aspect-square">
        <slot name="rightIcon"></slot>
      </div>
    </div>
    <div @scroll="itemsScroll" class="w-full h-full overflow-y-scroll">
      <div class="px-4 relative bg-dark-100 flex flex-col gap-6 mb-8 z-10 mt-12 transition-all duration-500"
        :class="!hideLabel ? 'opacity-100' : 'opacity-0'">
        <span class="font-semibold text-4xl">{{ label }}</span>
      </div>
      <slot></slot>
    </div>
  </div>
</template>

<style scoped></style>
