const listPaletteName = [
  'CloudColors_p',
  'LavaColors_p',
  'OceanColors_p',
  'ForestColors_p',
  'RainbowColors_p',
  'RainbowStripeColors_p',
  'PartyColors_p',
  'HeatColors_p',
  'Rainbow_gp'
]
const listPanelName = [ 
  "PanelType_P5_1_1",
  "PanelType_P5_2_2",
  "PanelType_P10_2_2"
]
const listColorTypeName = [
  'ColorType_Static',
  'ColorType_Rainbow',
  'ColorType_Square'
]
const listScreen = ['Screen_Calendar', 'Screen_Text', 'Screen_Counter']
const listFontName = [
  'NotoSerif_10pt7b',
  'NotoSerif_11pt7b',
  'NotoSerif_12pt7b',
  'NotoSerif_13pt7b',
  'Roboto_Medium10pt7b',
  'Roboto_Medium11pt7b',
  'Roboto_Medium12pt7b',
  'Roboto_Medium13pt7b'
]

const panelNameToString = paletteName => {
  if (paletteName === 'PanelType_P5_1_1') {
    return 'Một Tấm P5 1x1'
  }
  if (paletteName === 'PanelType_P5_2_2') {
    return 'Một Tấm P5 2x2'
  }
  if (paletteName === 'PanelType_P10_2_2') {
    return 'Bốn Tấm P10 2x2'
  }
}
const fontNameToString = font => {
  if (font === 'NotoSerif_10pt7b') {
    return 'Serif 10'
  }
  if (font === 'NotoSerif_11pt7b') {
    return 'Serif 11'
  }
  if (font === 'NotoSerif_12pt7b') {
    return 'Serif 12'
  }
  if (font === 'NotoSerif_13pt7b') {
    return 'Serif 13'
  }
  if (font === 'Roboto_Medium10pt7b') {
    return 'Roboto 10'
  }
  if (font === 'Roboto_Medium11pt7b') {
    return 'Roboto 11'
  }
  if (font === 'Roboto_Medium12pt7b') {
    return 'Roboto 12'
  }
  if (font === 'Roboto_Medium13pt7b') {
    return 'Roboto 13'
  }
}
const stringToFontName = (string) => {
  if (string === 'Serif 10') {
    return 'NotoSerif_10pt7b'
  }
  if (string === 'Serif 11') {
    return 'NotoSerif_11pt7b'
  }
  if (string === 'Serif 12') {
    return 'NotoSerif_12pt7b'
  }
  if (string === 'Serif 13') {
    return 'NotoSerif_13pt7b'
  }
  if (string === 'Roboto 10') {
    return 'Roboto_Medium10pt7b'
  }
  if (string === 'Roboto 11') {
    return 'Roboto_Medium11pt7b'
  }
  if (string === 'Roboto 12') {
    return 'Roboto_Medium12pt7b'
  }
  if (string === 'Roboto 13') {
    return 'Roboto_Medium13pt7b'
  }
}
const screenToString = screen => {
  if (screen === 'Screen_Calendar') {
    return 'Lịch vạn niên'
  }
  if (screen === 'Screen_Text') {
    return 'Chạy chữ'
  }
  if (screen === 'Screen_Counter') {
    return 'Đếm'
  }
}
const stringToPanelName = string => {
  if (string === 'Một Tấm P5 1x1') {
    return 'PanelType_P5_1_1'
  }
  if (string === 'Một Tấm P5 2x2') {
    return 'PanelType_P5_2_2'
  }
  if (string === 'Bốn Tấm P10 2x2') {
    return 'PanelType_P10_2_2'
  }
}
const stringToScreen = string => {
  if (string === 'Lịch vạn niên') {
    return 'Screen_Calendar'
  }
  if (string === 'Chạy chữ') {
    return 'Screen_Text'
  }
  if (string === 'Đếm') {
    return 'Screen_Counter'
  }
}
const listBackgroundEffectName = [
  'BackgroundEffect_None',
  'BackgroundEffect_GrowCirle',
  'BackgroundEffect_RunCirle',
  'BackgroundEffect_RunTriangle',
  'BackgroundEffect_RunText',
  'BackgroundEffect_Arrow',
  'BackgroundEffect_Ball'
]
const colorTypeToString = type => {
  if (type === 'ColorType_Static') {
    return 'Màu tĩnh'
  }
  if (type === 'ColorType_Rainbow') {
    return 'Màu cầu vồng'
  }
  if (type === 'ColorType_Square') {
    return 'Màu pixel'
  }
}
const stringToColorType = string => {
  if (string === 'Màu tĩnh') {
    return 'ColorType_Static'
  }
  if (string === 'Màu cầu vồng') {
    return 'ColorType_Rainbow'
  }
  if (string === 'Màu pixel') {
    return 'ColorType_Square'
  }
}
const backgroundEffectToString = effect => {
  if (effect === 'BackgroundEffect_None') {
    return 'Không hiệu ứng'
  }
  if (effect === 'BackgroundEffect_GrowCirle') {
    return 'Vòng tròn tỏa'
  }
  if (effect === 'BackgroundEffect_RunCirle') {
    return 'Vòng tròn chạy'
  }
  if (effect === 'BackgroundEffect_RunTriangle') {
    return 'Tam giác chạy'
  }
  if (effect === 'BackgroundEffect_RunText') {
    return 'Chữ chạy'
  }
  if (effect === 'BackgroundEffect_Arrow') {
    return 'Mũi tên'
  }
  if (effect === 'BackgroundEffect_Ball') {
    return 'Bóng nảy'
  }
}

const stringToBackgroudEffectName = string => {

  if (string === 'Không hiệu ứng') {
    return 'BackgroundEffect_None'
  }
  if (string === 'Vòng tròn tỏa') {
    return 'BackgroundEffect_GrowCirle'
  }
  if (string === 'Vòng tròn chạy') {
    return 'BackgroundEffect_RunCirle'
  }
  if (string === 'Tam giác chạy') {
    return 'BackgroundEffect_RunTriangle'
  }
  if (string === 'Chữ chạy') {
    return 'BackgroundEffect_RunText'
  }
  if (string === 'Mũi tên') {
    return 'BackgroundEffect_Arrow'
  }
  if (string === 'Bóng nảy') {
    return 'BackgroundEffect_Ball'
  }
}
const paletteNameToString = paletteName => {
  if (paletteName === 'CloudColors_p') {
    return 'Cloud Colors'
  }
  if (paletteName === 'LavaColors_p') {
    return 'Lava Colors'
  }
  if (paletteName === 'OceanColors_p') {
    return 'Ocean Colors'
  }
  if (paletteName === 'ForestColors_p') {
    return 'Forest Colors'
  }
  if (paletteName === 'RainbowColors_p') {
    return 'Rainbow Colors'
  }
  if (paletteName === 'RainbowStripeColors_p') {
    return 'Rainbow Stripe Colors'
  }
  if (paletteName === 'PartyColors_p') {
    return 'Party Colors'
  }
  if (paletteName === 'HeatColors_p') {
    return 'Heat Colors'
  }
  if (paletteName === 'Rainbow_gp') {
    return 'Rainbow'
  }
}
const stringToPaletteName = string => {
  if (string === 'Cloud Colors') {
    return 'CloudColors_p'
  }
  if (string === 'Lava Colors') {
    return 'LavaColors_p'
  }
  if (string === 'Ocean Colors') {
    return 'OceanColors_p'
  }
  if (string === 'Forest Colors') {
    return 'ForestColors_p'
  }
  if (string === 'Rainbow Colors') {
    return 'RainbowColors_p'
  }
  if (string === 'Rainbow Stripe Colors') {
    return 'RainbowStripeColors_p'
  }
  if (string === 'Party Colors') {
    return 'PartyColors_p'
  }
  if (string === 'Heat Colors') {
    return 'HeatColors_p'
  }
  if (string === 'Rainbow') {
    return 'Rainbow_gp'
  }
}
const paletteNameToClass = paletteName => {
  if (paletteName === 'CloudColors_p') {
    return 'palette palette-cloud'
  }
  if (paletteName === 'LavaColors_p') {
    return 'palette palette-lava'
  }
  if (paletteName === 'OceanColors_p') {
    return 'palette palette-ocean'
  }
  if (paletteName === 'ForestColors_p') {
    return 'palette palette-forest'
  }
  if (paletteName === 'RainbowColors_p') {
    return 'palette palette-rainbow'
  }
  if (paletteName === 'RainbowStripeColors_p') {
    return 'palette palette-rainbow-stripe'
  }
  if (paletteName === 'PartyColors_p') {
    return 'palette palette-party'
  }
  if (paletteName === 'HeatColors_p') {
    return 'palette palette-heat'
  }
  if (paletteName === 'Rainbow_gp') {
    return 'palette palette-rainbow'
  }
}

export default {
  listPaletteName,
  paletteNameToString,
  stringToPaletteName,
  paletteNameToClass,
  listBackgroundEffectName,
  backgroundEffectToString,
  stringToBackgroudEffectName,
  listColorTypeName,
  colorTypeToString,
  stringToColorType,
  listScreen,
  screenToString,
  stringToScreen,
  fontNameToString,
  stringToFontName,
  listFontName,
  paletteNameToString,
  listPanelName,
  panelNameToString,
  stringToPanelName

}
