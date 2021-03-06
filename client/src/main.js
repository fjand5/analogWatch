import Vue from 'vue'
import App from './App.vue'
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';
import locale from 'element-ui/lib/locale/lang/en'
import store from './store';
import ServicePlugin from './service'
Vue.use(ElementUI,  { locale })
Vue.use(ServicePlugin)




Vue.config.productionTip = false
new Vue({
  render: h => h(App),
  store: store
}).$mount('#app')

