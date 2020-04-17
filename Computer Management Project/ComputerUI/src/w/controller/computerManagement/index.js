import app from './App'
import dlgStyle0 from './DlgStyle0'
import dlgStyle1 from './DlgStyle1'
import dlgStyle2 from './DlgStyle2'
import viewLogin from './views/DlgStyle0/Login'
import viewMain from './views/DlgStyle0/Main'
import controllerError from '@/w/controller/error'

export default {
  router: {
    path: '/computerManagement/ui',
    component: app,
    children: [
      {
        path: '0',
        component: dlgStyle0,
        children: [
          { path: 'login', component: viewLogin },
          { path: 'main', component: viewMain }
        ]
      },
      {
        path: '1',
        component: dlgStyle1,
        children: []
      },
      {
        path: '2',
        component: dlgStyle2,
        children: []
      },
      controllerError.router
    ]
  }
}
