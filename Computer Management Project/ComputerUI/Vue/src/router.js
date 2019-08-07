import Vue from 'vue'
import Router from 'vue-router'

import controller_client from '@/w/controller/client'
import controller_error from '@/w/controller/error'

Vue.use(Router)

export default new Router({
  mode: 'history', //去掉URL中的/#/
  routes: [
    controller_client.router,
    controller_error.router
  ]
})