import app from './app'
import console_login from './views/login'
import console_management from './views/management'
import console_management_w_users from './views/management/w/users'
import console_management_w_management from './views/management/w/management'
import controller_error from '@/w/controller/error'

var meta = {
  title: "后台管理系统"
}

export default {
    router: {
      path:"/console",
      component: app, 
      children:[
        { path: '/', component: controller_error.error_404 },
        { path: 'login', component: console_login, meta: meta },
        { 
          path: 'management', 
          component: console_management,
          children:[
            { path: '/', redirect: 'w/users' },
            { path: 'w/users', component: console_management_w_users, meta: meta },
            { path: 'w/management', component: console_management_w_management, meta: meta },
          ] 
        },
        controller_error.router 
      ]
    }
}