import Vue from 'vue'
import VueRouter from 'vue-router'
import ControllerComputerManagement from '@/w/controller/computerManagement'
import controllerError from '@/w/controller/error'

Vue.use(VueRouter)

const routes = [
  ControllerComputerManagement.router,
  controllerError.router
]

const router = new VueRouter({
  mode: 'history',
  base: process.env.BASE_URL,
  routes
})

export default router
