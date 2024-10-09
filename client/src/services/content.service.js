import { baseUrl } from '~/utlis'
const setShadow = async shadow => {
  const data = await fetch(
    baseUrl +
      '/setShadow?' +
      new URLSearchParams({
        value: shadow
      })
  )
  const json = await data.json()
  return json
}
const setNextScreen = async () => {
  const data = await fetch(baseUrl + '/setNextScreen')
  const json = await data.json()
  return json
}
const setPreviousScreen = async () => {
  const data = await fetch(baseUrl + '/setPreviousScreen')
  const json = await data.json()
  return json
}
const setScreen = async (screen) => {
  const data = await fetch(
    baseUrl +
      '/setScreen?' +
      new URLSearchParams({
        value: screen
      })
  )
  const json = await data.json()
  return json
}


const setContentColorType = async color => {
  const data = await fetch(
    baseUrl +
      '/setContentColorType?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
const getContent = async () => {
  const data = await fetch(baseUrl + '/getContent')
  const json = await data.json()
  return json
}

const setContentColor = async color => {
  const data = await fetch(
    baseUrl +
      '/setContentColor?' +
      new URLSearchParams({
        value: color
      })
  )
  const json = await data.json()
  return json
}
const setContentBrightness = async brightness => {
  const data = await fetch(
    baseUrl +
      '/setContentBrightness?' +
      new URLSearchParams({
        value: brightness
      })
  )
  const json = await data.json()
  return json
}
export default {
  getContent,
  setShadow,
  setNextScreen,
  setPreviousScreen,
  setScreen,
  setContentColorType,
  setContentColor,
  setContentBrightness
}
