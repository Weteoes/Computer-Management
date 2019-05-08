import Vue from 'vue'
import Router from 'vue-router'

import controller_client_apk from '@/w/controller/client_apk'
import controller_console from '@/w/controller/console'
import controller_error from '@/w/controller/error'

Vue.use(Router)

export default new Router({
  mode: 'history', //去掉URL中的/#/
  routes: [
    controller_client_apk.router,
    controller_console.router,
    controller_error.router
  ]
})