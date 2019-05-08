<?php
function addHeader() {
    header('Content-type: application/json');
    header('Access-Control-Allow-Origin:*');
    header('Access-Control-Allow-Method:POST,GET');
    header("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, token, Accept");
    header("X-Powered-By:Weteoes");
}