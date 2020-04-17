<template>
    <router-view />
</template>

<script>
export default {
  data () {
    return {
      w: window.weteoes
    }
  },
  methods: {
    ready: function () { },
    readyCEFSize: function (div) {
      const a = document.querySelector(div)
      const w = a.offsetWidth
      const h = a.offsetHeight
      this.log('readyCEFSize', 'width:', w, 'height:', h)
      this.w.softwareApi.dlg.size(w, h)
    },
    log: function (...msg) {
      console.log(...msg)
    }
  },
  mounted () {}
}
</script>
