import app from './app'
import login from './views/login'
import main from './views/main'
import controller_error from '@/w/controller/error'

export default {
    router : {
        path: '/client',
        component: app ,
        children:[
          { path: '/', component: controller_error.error_404 },
          { path: 'login', component: login, meta: { title: "登录" }},
          { path: 'main', component: main, meta: { title: "主窗口" } },
          controller_error.router
        ]
    }
}