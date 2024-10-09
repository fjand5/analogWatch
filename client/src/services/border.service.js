import { baseUrl } from '~/utlis'
const setBorderWidth = async borderWidth => {
  const data = await fetch(
    baseUrl +
      '/setBorderWidth?' +
      new URLSearchParams({
        value: borderWidth
      })
  )
  const json = await data.json()
  return json
}
const setBorderPalette = async palette => {
  const data = await fetch(
    baseUrl +
      '/setBorderPalette?' +
      new URLSearchParams({
        value: palette
      })
  )
  const json = await data.json()
  return json
}
const setBorderTick = async tick => {
  const data = await fetch(
    baseUrl +
      '/setBorderTick?' +
      new URLSearchParams({
        value: tick
      })
  )
  const json = await data.json()
  return json
}
const getBorder = async () => {
  const data = await fetch(baseUrl + '/getBorder')
  const json = await data.json()
  return json
}
export default {
  getBorder,
  setBorderWidth,
  setBorderTick,
  setBorderPalette
}
