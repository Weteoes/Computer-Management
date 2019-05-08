<?php
namespace Weteoes;
class LoadingClass {
    public function include_Session() {
		include_once(operating_Management_path."../Session.php");
    }
    public function include_Login() {
		include_once(operating_Management_path."../Login.php");
    }
}