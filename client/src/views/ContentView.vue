<script setup>
import { onMounted, reactive, ref, watch } from "vue";
import GroupItem from "~/components/base/GroupItem.vue";
import { ContentService } from "~/services";
import { StringData } from "~/utlis";
import MenuItem from "../components/MenuItem.vue";
import Color from "../components/icon/Color.vue";
import BaseView from "./BaseView.vue";
import ColorPicker from "../components/ColorPicker.vue";
import SelectList from "../components/SelectList.vue";
import SliderItem from "../components/SliderItem.vue";
import Light from "../components/icon/Light.vue";

const showSelectColorType = ref(false);

const selectedColorType = ref({
  text: "",
  label: "",
});

const contentData = reactive({
  colorType: undefined,
  color: "#0000",
  brightness: 127,
});
onMounted(async () => {
  const result = await ContentService.getContent();
  contentData.colorType = result["colorType"];
  contentData.color = result["color"];
  contentData.brightness = result["brightness"];

  selectedColorType.value.text = StringData.colorTypeToString(
    contentData.colorType
  );
});

watch(
  () => contentData.color,
  async (n, o) => {
    if (o === undefined) return;
    await ContentService.setContentColor(n);
  }
);

watch(
  () => contentData.brightness,
  async (n, o) => {
    if (o === undefined) return;

    await ContentService.setContentBrightness(n);
  }
);
watch(selectedColorType, async (n, o) => {
  if (o === undefined) return;
  await ContentService.setContentColorType(
    StringData.stringToColorType(n.text)
  );
});
</script>

<template>
  <div class="w-full h-full">
    <BaseView label="Nội dung chính">
      <GroupItem label="Độ sáng, tốc độ">
        <div class="relative w-full px-4">
          <SliderItem
            class="mb-2"
            :icon="Light"
            label="Độ sáng đồng hồ"
            v-model="contentData.brightness"
            :min="0"
            :max="255"
            :step="5"
          >
          </SliderItem>
        </div>
      </GroupItem>

      <GroupItem label="Đồng Hồ">
        <div class="relative w-full px-4">
          <MenuItem
            @itemClick="() => (showSelectColorType = true)"
            label="Chọn màu"
            :detail="`Màu hiện tại [${selectedColorType?.text || ''}]`"
          >
            <template #icon>
              <div class="h-8 aspect-square">
                <Color />
              </div>
            </template>
          </MenuItem>
        </div>

        <Transition name="bounce">
          <div
            v-if="
              showSelectColorType == false &&
              selectedColorType.text ===
                StringData.colorTypeToString('ColorType_Static')
            "
            class="w-full h-full flex justify-center mb-4"
          >
            <ColorPicker v-model:color="contentData.color" />
          </div>
        </Transition>

        <Transition name="bounce">
          <SelectList
            :closeWhenSelect="true"
            v-if="showSelectColorType"
            v-model:show="showSelectColorType"
            v-model:selected-item="selectedColorType"
            label="Chọn màu"
            :list-item="
              StringData.listColorTypeName.map((colorType) => ({
                text: StringData.colorTypeToString(colorType),
              }))
            "
          >
          </SelectList>
        </Transition>
      </GroupItem>
    </BaseView>
  </div>
</template>

<style scoped></style>
