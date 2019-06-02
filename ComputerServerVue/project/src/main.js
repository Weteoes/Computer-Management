import Vue from 'vue'
import app from './app.vue'
import router from './router'
import axios from 'axios' //ajax

Vue.config.devtools = false
Vue.config.productionTip = false
Vue.prototype.debug = false
Vue.prototype.axios = axios //ajax
//element
import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'
Vue.use(ElementUI)
//element End

router.beforeEach((to, from, next) => {
  /* 路由发生变化修改页面title */
  if (to.meta.title) {
    document.title = to.meta.title
  }
  next()
})

// new Vue需要在最后
new Vue({
  router,
  render: h => h(app),
  mounted () {
    document.dispatchEvent(new Event('render-event'))
  } 
}).$mount('#app')