<script setup>
import { onMounted, ref } from "vue";
const { color } = defineProps({ color: { type: String, default: "ff0000" } });
const emit = defineEmits(["update:color"]);
const mainColor = ref("");
const mainColorPosition = ref(0);
onMounted(() => {
  mainColor.value = color.startsWith("#") ? color.substring(1) : color;
  const { r, g, b } = hexToRgb(color);
  if (r === 255 && b === 0) {
    mainColorPosition.value = (0.1666 * g) / 255;
  } else if (g === 255 && b === 0) {
    mainColorPosition.value = 0.3333 - (r * 0.1666) / 255;
  } else if (r === 0 && g === 255) {
    mainColorPosition.value = (b * 0.1666) / 255 + 0.3333;
  } else if (g === 0 && b === 255) {
    mainColorPosition.value = (r * 0.1666) / 255 + 0.6666;
  } else if (r === 255 && g === 0) {
    mainColorPosition.value = 1 - (b * 0.1666) / 255;
  } else mainColorPosition.value = -1;
});
const hexToRgb = (hex) => {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result
    ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16),
      }
    : null;
};
const rgbToHex = (r, g, b) => {
  return ((1 << 24) | (r << 16) | (g << 8) | b).toString(16).slice(1);
};
const selectMainColor = (e) => {
  mainColorPosition.value = e.offsetX / e.target.clientWidth;
  const v = mainColorPosition.value;
  let r, g, b;
  if (v >= 0 && v < 0.1666) {
    r = 255;
    g = (255 * v) / 0.1666;
    b = 0;
  }
  if (v >= 0.1666 && v < 0.3333) {
    r = (255 * (0.3333 - v)) / 0.1666;
    g = 255;
    b = 0;
  }
  if (v >= 0.3333 && v < 0.5) {
    r = 0;
    g = 255;
    b = (255 * (v - 0.3333)) / 0.1666;
  }
  if (v >= 0.5 && v < 0.6666) {
    r = 0;
    g = (255 * (0.6666 - v)) / 0.1666;
    b = 255;
  }
  if (v >= 0.6666 && v < 0.8333) {
    r = (255 * (v - 0.6666)) / 0.1666;
    g = 0;
    b = 255;
  }
  if (v >= 0.8333 && v <= 1) {
    r = 255;
    g = 0;
    b = (255 * (1 - v)) / 0.1666;
  }
  mainColor.value = rgbToHex(r, g, b);
  emit("update:color", mainColor.value);
};
const selectWhite = () => {
  mainColor.value = "ffffff";
  mainColorPosition.value = -1;
  emit("update:color", mainColor.value);
};
</script>

<template>
  <div class="w-full px-4 flex justify-center gap-2 items-center">
    <div
      @click="selectMainColor"
      class="main-color rounded-full w-full h-4 relative"
    >
      <div
        :style="{
          left: mainColorPosition * 100 + '%',
          background: '#' + mainColor,
        }"
        class="absolute transition-all shadow-md bottom-[50%] translate-y-[50%] translate-x-[-50%] w-8 h-8 border border-dark-500 rounded-full bg-dark-300 pointer-events-none"
      ></div>
    </div>
    <!-- <div @click="selectWhite" class=" w-8 aspect-square border rounded-full bg-white">
    </div> -->
  </div>
</template>

<style scoped>
.main-color {
  background: linear-gradient(
    to right,
    rgb(255, 0, 0) 0%,
    rgb(255, 255, 0) 16.66%,
    rgb(0, 255, 0) 33.33%,
    rgb(0, 255, 255) 50%,
    rgb(0, 0, 255) 66.66%,
    rgb(255, 0, 255) 83.33%,
    rgb(255, 0, 0) 100%
  );
  background: -webkit-linear-gradient(
    left,
    rgb(255, 0, 0) 0%,
    rgb(255, 255, 0) 16.66%,
    rgb(0, 255, 0) 33.33%,
    rgb(0, 255, 255) 50%,
    rgb(0, 0, 255) 66.66%,
    rgb(255, 0, 255) 83.33%,
    rgb(255, 0, 0) 100%
  );
  background: -moz-linear-gradient(
    left,
    rgb(255, 0, 0) 0%,
    rgb(255, 255, 0) 16.66%,
    rgb(0, 255, 0) 33.33%,
    rgb(0, 255, 255) 50%,
    rgb(0, 0, 255) 66.66%,
    rgb(255, 0, 255) 83.33%,
    rgb(255, 0, 0) 100%
  );
  background: -ms-linear-gradient(
    left,
    rgb(255, 0, 0) 0%,
    rgb(255, 255, 0) 16.66%,
    rgb(0, 255, 0) 33.33%,
    rgb(0, 255, 255) 50%,
    rgb(0, 0, 255) 66.66%,
    rgb(255, 0, 255) 83.33%,
    rgb(255, 0, 0) 100%
  );
}
</style>
