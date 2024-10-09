import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '../views/HomeView.vue'
import WiFiView from '~/views/WiFiView.vue'
import SetWiFiView from '~/views/SetWiFiView.vue'
import SystemView from '~/views/SystemView.vue'
import DisplayView from '~/views/DisplayView.vue'
import BorderView from '~/views/BorderView.vue'
import BackgroundView from '~/views/BackgroundView.vue'
import ContentView from '~/views/ContentView.vue'

const router = createRouter({
  mode: 'history',

  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView
    },
    {
      path: '/wifi',
      name: 'wifi',
      component: WiFiView
    },
    {
      path: '/setWifi',
      name: 'setWifi',
      component: SetWiFiView
    },
    {
      path: '/system',
      name: 'system',
      component: SystemView
    },
    {
      path: '/display',
      name: 'display',
      component: DisplayView
    },
    {
      path: '/border',
      name: 'border',
      component: BorderView
    },
    {
      path: '/background',
      name: 'background',
      component: BackgroundView
    },
    {
      path: '/content',
      name: 'content',
      component: ContentView
    },
    { path: '/:pathMatch(.*)*', component: HomeView }
  ]
})

export default router
