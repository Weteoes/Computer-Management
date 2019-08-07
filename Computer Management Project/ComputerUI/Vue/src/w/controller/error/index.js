import error_404 from './views/404'

export default {
    router: {
      path:"*",
      component: error_404
    },
    error_404: error_404
}