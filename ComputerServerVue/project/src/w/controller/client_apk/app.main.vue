<template>
  <router-view/>
</template>

<!-- nav.css -->
<style>
.main_nav {
    width: 100%;
    height: 60px;
    background:url('/Weteoes/Client_apk/Main/index/image/top_background.png');
    background-size: 100% 100%;
}
.main_nav .one {
    width: 100%;
    height: 20px;
}
.main_nav_two { /* main_nav .two 高度 */
    height: 40px;
    line-height: 40px;
}
.main_nav .two {
    width: 100%;
}
.main_nav .two .left {
    width: 5px;
}
.main_nav_inline {
    display: inline-block;
    vertical-align: top;
}
.main_nav .title {
    color: #fff;
    font-size: 18px;
    padding-left: 5px;
}
.main_nav_menu {
    width: 36px;
}
.main_nav .menu {
    padding-top: 2px;
}
</style>
