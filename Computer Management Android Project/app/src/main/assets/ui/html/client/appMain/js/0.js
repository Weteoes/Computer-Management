(function() {
  ready();
  function ready() {
    new Vue({
      el: "#app",
      data() {
        return {
          w: window.Weteoes,
        };
      },
      methods: {},
      mounted() {
        this.w.function.ready(); // 初始化
        // 判断是否登录
        this.w.function.isLogin(
          () => {
            //登录成功
            location.href = this.w.url.main;
          },
          () => {
            //登录失败
            location.href = this.w.url.login;
          }
        );
        // 判断是否登录 End
      }
    });
  }
})();
