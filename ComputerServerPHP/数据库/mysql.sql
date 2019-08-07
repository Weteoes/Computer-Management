/*
 Navicat Premium Data Transfer

 Source Server         : server
 Source Server Type    : MySQL
 Source Server Version : 50717
 Source Host           : server.weteoes.cn:3306
 Source Schema         : computer_management

 Target Server Type    : MySQL
 Target Server Version : 50717
 File Encoding         : 65001

 Date: 04/08/2019 17:46:55
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for login
-- ----------------------------
DROP TABLE IF EXISTS `login`;
CREATE TABLE `login`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `user` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `pass` varchar(64) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `management` int(1) UNSIGNED ZEROFILL NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 6 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of login
-- ----------------------------
INSERT INTO `login` VALUES (5, 'sj58uhsh554hbdh1', 'cs', '123456', 0);
INSERT INTO `login` VALUES (1, 'WeteoesUID', 'Weteoes', 'Computer20000125', 1);

SET FOREIGN_KEY_CHECKS = 1;
