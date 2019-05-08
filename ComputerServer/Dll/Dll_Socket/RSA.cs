using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Security;
using System;
using System.Security.Cryptography;
using System.Text;

namespace Weteoes
{
    public class RSAClass
    {
        //public String A_PublicKey = "<RSAKeyValue><Modulus>0pf6nAbz1e0q6gKxbdZUNvFsi5wn4hIPsb82dnac7o4Crfoz4KFc/MNavirwsjkCsNBTBPuFle5560yrPL5roXog4nfol/xAKi7D+zqJil+DUmNYqkN5gHnrPIT+r89WadJM4EKaOE/sKJ1dUF94VJnR+mD2k9WXa3YmW+eGxvPHbUh1aHFh1k1vgZOIBtNyXDDXH/sULQE1b+ZddMLdeIlrO0Wdvkg23mM76dSQmLH2WMF9XMgUUuHTUllMRwJdWQf/XAI8GLvEtMP88ZYsJso3c5z1VVi6Fmzqc/tJXKLBU4qT3NYUtBSkDP3lM2QV3W9zzlRIiplvQ8Fd90ZqVQ==</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
        public String B_PrivateKey = "<RSAKeyValue><Modulus>0pf6nAbz1e0q6gKxbdZUNvFsi5wn4hIPsb82dnac7o4Crfoz4KFc/MNavirwsjkCsNBTBPuFle5560yrPL5roXog4nfol/xAKi7D+zqJil+DUmNYqkN5gHnrPIT+r89WadJM4EKaOE/sKJ1dUF94VJnR+mD2k9WXa3YmW+eGxvPHbUh1aHFh1k1vgZOIBtNyXDDXH/sULQE1b+ZddMLdeIlrO0Wdvkg23mM76dSQmLH2WMF9XMgUUuHTUllMRwJdWQf/XAI8GLvEtMP88ZYsJso3c5z1VVi6Fmzqc/tJXKLBU4qT3NYUtBSkDP3lM2QV3W9zzlRIiplvQ8Fd90ZqVQ==</Modulus><Exponent>AQAB</Exponent><P>5ley6xyvzppK+qRtZaLT3tjNtdK6V68FAO/HNtOwadRhmeNQjGICDRa+larvn8nCSLQCd1AyjylYNQ0ls6P/8wLBv2/6nDojY02HXE3PhcV9O4yV04YYQo6grZAOMQCEg8SKD+7lUFRA9xHQNqL77rAhpr9OIwPtCrVhvktDyL8=</P><Q>6g0iBfyi9t8qmHhVbSzYXZRJyPwztMVlQCjykRigUona3RFBUHyZkA01qLTk4h6Qrn8FF1ALGHq8/zLwMrGMeBazB63Toy3TkRSjlS+qFF85jizA08/kgc2CITyegHiAOpnPTS7nUwkNWvuhi1TkezmpzG8i9B4PCclWtL4Qnes=</Q><DP>38Q+iey6VajKQidOJzhBPvG7FXF7mQbrg3dsPjTz4jtx/X84lsf3WiPITblbRA1Kcjp9Us9T7oOprw/wmk0trjP1aDYubWqFSkjcwKzOdxPdjuYJ/wz7sFzCdxnEz5HDKgbaYJQhrSHMYripXwqCV+Q/LLAYBiggNRDzvVt8pB0=</DP><DQ>EYC766Cx+y5DPDW7hbeV0qG1Rt99amZcpQiq4yjpTGLcyC1zKfa3cStbuOsWNsa8YSBEnDKzMbh0C82eYtweOhjQeKGKMyjJKo9VkGGJIY7hef1kyjJAz2gz9BJZdBgO1tMLyqTYTcBejFBHC2lk0MZGKXCiN4lL7Jpu7oNMMNM=</DQ><InverseQ>DMrtqIdprIE2Em4e9UCBMGe6gBnPi591dHWsxkDgPzTDjOkzhXIjvJE0LnFs8TnS6OZpgczU9ehw/scRHrmJ/tjyIlOAX+0GhwdM//JEbggtmD89QWWyrG4s2opO06scY4qsSfkoIwJafI0nEfNMeCJkR0vN3wuKBEOPZG+4osI=</InverseQ><D>wTZu13gJftx54vlVkFB0M3SNAgnjDadEfu/QKB/rG3NvQe+saQujJMSXHKKI8vsbXN3FTWz2wvhpI1jUQobyeNR0F1OsMsVcmVcOuBCc4DeBZLWBQ7VkZFt3V68tfF/eCHjJz3dLxx6MrTazxmnRHM2DuRP9JuVwZ0efKfLh1OVqoHZbjbun+gaSTmyt1kxDT3sRbEtoKhNVWiWti+IqPNcdx0BkVNMmt8XdGB+1WlvN++76+kCGNlnGGBt+DGsKNwn7MBbCX+wytZV0zLLpwr3QjnayWPcmHCSh+n5BHLR8QjlE4UDom5SY5rzMFm5X9NEjQY5QZor4HI5x/J1ugQ==</D></RSAKeyValue>";
        public String A_PublicKey = "<RSAKeyValue><Modulus>p+i+Wnw6H0m/2oYEzuJL8+VL2YvZvInM75lcnbD+JVGeQqEpX4W0qO283olJeKFMEnWdFuhsF0oxPvTyqjW07tnaUMvIl+eHRPzdfPvQh8a0HnOWMzaxXjou9vhLqNjsCaLu6Cmjb23Z1kDPDh31rI4iopCtEN20Eb6IXFZEBKHWyBEY4MO6KRaDycSJTle3bob7Av5K19n/qqCD9WVFlDbTBIixxsJ0Y+ngigHIpubPBBh5TfkQFPbIBRmbG0KZudEInKWPFwBD1TC6uQjRjZqhbMdAJbY/Q3vJbMwbCGKcZCAhXIkTMPnEqdN2bmiKf/U1fnyPuSX2xdNiSTbubQ==</Modulus><Exponent>AQAB</Exponent></RSAKeyValue>";
        //public String B_PrivateKey = "<RSAKeyValue><Modulus>p+i+Wnw6H0m/2oYEzuJL8+VL2YvZvInM75lcnbD+JVGeQqEpX4W0qO283olJeKFMEnWdFuhsF0oxPvTyqjW07tnaUMvIl+eHRPzdfPvQh8a0HnOWMzaxXjou9vhLqNjsCaLu6Cmjb23Z1kDPDh31rI4iopCtEN20Eb6IXFZEBKHWyBEY4MO6KRaDycSJTle3bob7Av5K19n/qqCD9WVFlDbTBIixxsJ0Y+ngigHIpubPBBh5TfkQFPbIBRmbG0KZudEInKWPFwBD1TC6uQjRjZqhbMdAJbY/Q3vJbMwbCGKcZCAhXIkTMPnEqdN2bmiKf/U1fnyPuSX2xdNiSTbubQ==</Modulus><Exponent>AQAB</Exponent><P>25OewzXs34cLP53ZdFRyYewx0weOzNbrJNS2YeW/lnlQeUdbjOaY6Tddc+Xm/HTm6qf+sPdcUthQVyUrjFrkOh2cwq/MTMJbowI3a2Kwz3ua1mF4zMBngMCgY5sD04HWMG63yaH9kK4OgL/K7QBzQ6H8oYaRtwnUmttOS3CZdOM=</P><Q>w8MMy/TIYX2YsRNDlirnWE2daQ2GiizSuZq0X6RZGdYAOjPLVxLd7laeCMXpmkWdFF6nDt5ubcn68WSlnRk+NBaOQQ7LnHyxw1AGPS6I5yOEZZg6dQV9xgCPmaMZWIlU8r+bCXmS+BEjPg42MXNlplPwfDaHXITl+HeqHKdhwG8=</Q><DP>c2l5JmQeuDLUH8EJPlLwuDWczq4HSfWhLP+9SWGoPSBQwx5VqY6/Sr32Gef6bDHJ+gcJIN0zorveJp/77s8LbNyJu+8JNENoRRryJDiAdN4kOZCMHRr4jD0zUId3EGILQfPAGHRTwgsqxlOJBt+YtjDbh88iohHBtQ+WbKKnlj8=</DP><DQ>tEMbuYPCMOOygvw2NEV1mn5+AIqP5RS5RmgKyDdSRNQmiXHAQIIDEsF37KQyI/kOV/+A3dQ846QmC7qeNjdUbCqI+6dgHs1D85Hw7M25Cv5NoC+5RKC13GoP0W26nSh4rL97SBJHH17IkRANHyQf6jVJMVgU9UD7cvzeDFylSsk=</DQ><InverseQ>1OYpSBsx7rRDu8rIaRb/sPKJ3Y/j5Gs64rERWEpMk0kbC6CxMxpKnzFNydt9XjiANPBaoKGNnJXqupT+1LhlF0FuSGW7fKtqaZAi2eI/+8NBldyso7TCR000zShQYhdiUXOzBj2ZijE1nKT84Nav3CbwmB8AteSPr8zuR2zaWJ0=</InverseQ><D>QtQbjyAKchGETpEwsLbYzAXjHn7O9n9SFbrQZeLgBDJr7tD+CorI0MNufJPfridkg6RUFZ4EB3D8ELalLqGZlccXYTj6aZs493g9H1WKNcAcSFJw4YlPJtW5g4pncpiDuYIj3DtWVS8/mErLHi9GbJtVpaY3e5MB7F4NH9Ml10F9T6C+Iru38422hgWELxZgBO9tCnvBMBbSEyLecp5UesusmZ1Xr/H8RhlPnkuuNwtNBO74aqDj9hvT7Vl0ArSHHfZp0YdVDpIXH9tmynlfmrN6OUcn4zLk9db9OUdez2GY2JUSJEHHuGmIC2m4on0vxEBcVBgofymmtzv4gEfo8Q==</D></RSAKeyValue>";



        #region RSA 的密钥产生
        /// <summary>
        /// RSA产生密钥
        /// </summary>
        /// <param name="xmlKeys">私钥</param>
        /// <param name="xmlPublicKey">公钥</param>
        public void RSAKey(out string xmlKeys, out string xmlPublicKey)
        {
            try
            {
                System.Security.Cryptography.RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(2048);
                xmlKeys = rsa.ToXmlString(true);
                xmlPublicKey = rsa.ToXmlString(false);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion
        #region RSA函数
        //############################################################################## 
        //RSA 方式加密 
        //KEY必须是XML的形式,返回的是字符串 
        //该加密方式有长度限制的！
        //############################################################################## 
        private string RSA_w(ICipherParameters key, string strEncryptString, bool encode) //encode true 加密 false 解密
        {
            string result = "";
            try
            {
                byte[] DataToEncrypt = Encoding.UTF8.GetBytes(strEncryptString);
                if (!encode) { //解密
                    DataToEncrypt = Convert.FromBase64String(strEncryptString);
                }
                IBufferedCipher c = CipherUtilities.GetCipher("RSA/ECB/PKCS1Padding");// 参数与Java中加密解密的参数一致
                c.Init(encode, key);
                byte[] outBytes = c.DoFinal(DataToEncrypt);
                if (encode) { //加密
                     result = Convert.ToBase64String(outBytes);
                }
                else { //解密
                    result = (new UTF8Encoding()).GetString(outBytes);
                }
            }
            catch (Exception error) {
                throw error;
            }       
            return result;
        }
        private sbyte[] Modify_Byte(byte[] data) {
            sbyte[] result = new sbyte[data.Length];
            for (int i = 0; i < data.Length; i++) {
                byte b = data[i];
                if (b > 127)
                { //超出范围
                    int c = -(256 - b);
                    result[i] = (sbyte)c;
                }
                else {
                    result[i] = (sbyte)b;
                }
            }
            return result;
        }
        private byte[] Modify_CByte(byte[] data)
        {
            byte[] result = new byte[data.Length];
            for (int i = 0; i < data.Length; i++)
            {
                byte b = data[i];
                if (b <= 127) {
                    int c = b + 128;
                    result[i] = (byte)c;
                }
                else
                { //超出范围
                    int c = -(256 - b) + 128;
                    result[i] = (byte)c;
                }
            }
            return result;
        }
        public string Send_PublicEncode(string data)
        {
            RSACryptoServiceProvider rsaKey = new RSACryptoServiceProvider();
            rsaKey.FromXmlString(A_PublicKey);
            ICipherParameters Key = DotNetUtilities.GetRsaPublicKey(rsaKey);
            return RSA_w(Key, data, true);
        }
        public string Send_PublicUnEncode(string data)
        {
            //RSACryptoServiceProvider rsaKey = new RSACryptoServiceProvider();
            //rsaKey.FromXmlString(publicKey);
            //ICipherParameters Key = DotNetUtilities.GetRsaPublicKey(rsaKey);
            //return RSA_w(Key, data, false);
            return "No";
        }
        public string Accept_PrivateEncode(string data)
        {
            //RSACryptoServiceProvider rsaKey = new RSACryptoServiceProvider();
            //rsaKey.FromXmlString(privateKey);
            //AsymmetricCipherKeyPair keyPair = DotNetUtilities.GetKeyPair(rsaKey);
            //return RSA_w(keyPair.Private, data, true);
            return "No";
        }
        public string Accept_PrivateUnEncode(string data) //接收后通过私钥解密
        {
            RSACryptoServiceProvider rsaKey = new RSACryptoServiceProvider();
            rsaKey.FromXmlString(B_PrivateKey);
            AsymmetricCipherKeyPair keyPair = DotNetUtilities.GetKeyPair(rsaKey);
            return RSA_w(keyPair.Private, data, false);
        }
        #endregion
        #region RSA数字签名
        #region 获取Hash描述表        
        /// <summary>
        /// 获取Hash描述表
        /// </summary>
        /// <param name="strSource">待签名的字符串</param>
        /// <param name="HashData">Hash描述</param>
        /// <returns></returns>
        public bool GetHash(string strSource, ref byte[] HashData)
        {
            try
            {
                byte[] Buffer;
                System.Security.Cryptography.HashAlgorithm MD5 = System.Security.Cryptography.HashAlgorithm.Create("MD5");
                Buffer = System.Text.Encoding.GetEncoding("GB2312").GetBytes(strSource);
                HashData = MD5.ComputeHash(Buffer);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// 获取Hash描述表
        /// </summary>
        /// <param name="strSource">待签名的字符串</param>
        /// <param name="strHashData">Hash描述</param>
        /// <returns></returns>
        public bool GetHash(string strSource, ref string strHashData)
        {
            try
            {
                //从字符串中取得Hash描述 
                byte[] Buffer;
                byte[] HashData;
                System.Security.Cryptography.HashAlgorithm MD5 = System.Security.Cryptography.HashAlgorithm.Create("MD5");
                Buffer = System.Text.Encoding.GetEncoding("GB2312").GetBytes(strSource);
                HashData = MD5.ComputeHash(Buffer);
                strHashData = Convert.ToBase64String(HashData);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// 获取Hash描述表
        /// </summary>
        /// <param name="objFile">待签名的文件</param>
        /// <param name="HashData">Hash描述</param>
        /// <returns></returns>
        public bool GetHash(System.IO.FileStream objFile, ref byte[] HashData)
        {
            try
            {
                //从文件中取得Hash描述 
                System.Security.Cryptography.HashAlgorithm MD5 = System.Security.Cryptography.HashAlgorithm.Create("MD5");
                HashData = MD5.ComputeHash(objFile);
                objFile.Close();
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// 获取Hash描述表
        /// </summary>
        /// <param name="objFile">待签名的文件</param>
        /// <param name="strHashData">Hash描述</param>
        /// <returns></returns>
        public bool GetHash(System.IO.FileStream objFile, ref string strHashData)
        {
            try
            {
                //从文件中取得Hash描述 
                byte[] HashData;
                System.Security.Cryptography.HashAlgorithm MD5 = System.Security.Cryptography.HashAlgorithm.Create("MD5");
                HashData = MD5.ComputeHash(objFile);
                objFile.Close();
                strHashData = Convert.ToBase64String(HashData);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion

        #region RSA签名
        /// <summary>
        /// RSA签名
        /// </summary>
        /// <param name="strKeyPrivate">私钥</param>
        /// <param name="HashbyteSignature">待签名Hash描述</param>
        /// <param name="EncryptedSignatureData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureFormatter(string strKeyPrivate, byte[] HashbyteSignature, ref byte[] EncryptedSignatureData)
        {
            try
            {
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();

                RSA.FromXmlString(strKeyPrivate);
                System.Security.Cryptography.RSAPKCS1SignatureFormatter RSAFormatter = new System.Security.Cryptography.RSAPKCS1SignatureFormatter(RSA);
                //设置签名的算法为MD5 
                RSAFormatter.SetHashAlgorithm("MD5");
                //执行签名 
                EncryptedSignatureData = RSAFormatter.CreateSignature(HashbyteSignature);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// RSA签名
        /// </summary>
        /// <param name="strKeyPrivate">私钥</param>
        /// <param name="HashbyteSignature">待签名Hash描述</param>
        /// <param name="m_strEncryptedSignatureData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureFormatter(string strKeyPrivate, byte[] HashbyteSignature, ref string strEncryptedSignatureData)
        {
            try
            {
                byte[] EncryptedSignatureData;
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPrivate);
                System.Security.Cryptography.RSAPKCS1SignatureFormatter RSAFormatter = new System.Security.Cryptography.RSAPKCS1SignatureFormatter(RSA);
                //设置签名的算法为MD5 
                RSAFormatter.SetHashAlgorithm("MD5");
                //执行签名 
                EncryptedSignatureData = RSAFormatter.CreateSignature(HashbyteSignature);
                strEncryptedSignatureData = Convert.ToBase64String(EncryptedSignatureData);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// RSA签名
        /// </summary>
        /// <param name="strKeyPrivate">私钥</param>
        /// <param name="strHashbyteSignature">待签名Hash描述</param>
        /// <param name="EncryptedSignatureData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureFormatter(string strKeyPrivate, string strHashbyteSignature, ref byte[] EncryptedSignatureData)
        {
            try
            {
                byte[] HashbyteSignature;
                HashbyteSignature = Convert.FromBase64String(strHashbyteSignature);
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPrivate);
                System.Security.Cryptography.RSAPKCS1SignatureFormatter RSAFormatter = new System.Security.Cryptography.RSAPKCS1SignatureFormatter(RSA);
                //设置签名的算法为MD5 
                RSAFormatter.SetHashAlgorithm("MD5");
                //执行签名 
                EncryptedSignatureData = RSAFormatter.CreateSignature(HashbyteSignature);

                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        /// <summary>
        /// RSA签名
        /// </summary>
        /// <param name="strKeyPrivate">私钥</param>
        /// <param name="strHashbyteSignature">待签名Hash描述</param>
        /// <param name="strEncryptedSignatureData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureFormatter(string strKeyPrivate, string strHashbyteSignature, ref string strEncryptedSignatureData)
        {
            try
            {
                byte[] HashbyteSignature;
                byte[] EncryptedSignatureData;
                HashbyteSignature = Convert.FromBase64String(strHashbyteSignature);
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPrivate);
                System.Security.Cryptography.RSAPKCS1SignatureFormatter RSAFormatter = new System.Security.Cryptography.RSAPKCS1SignatureFormatter(RSA);
                //设置签名的算法为MD5 
                RSAFormatter.SetHashAlgorithm("MD5");
                //执行签名 
                EncryptedSignatureData = RSAFormatter.CreateSignature(HashbyteSignature);
                strEncryptedSignatureData = Convert.ToBase64String(EncryptedSignatureData);
                return true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion

        #region RSA 签名验证
        /// <summary>
        /// RSA签名验证
        /// </summary>
        /// <param name="strKeyPublic">公钥</param>
        /// <param name="HashbyteDeformatter">Hash描述</param>
        /// <param name="DeformatterData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureDeformatter(string strKeyPublic, byte[] HashbyteDeformatter, byte[] DeformatterData)
        {
            try
            {
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPublic);
                System.Security.Cryptography.RSAPKCS1SignatureDeformatter RSADeformatter = new System.Security.Cryptography.RSAPKCS1SignatureDeformatter(RSA);
                //指定解密的时候HASH算法为MD5 
                RSADeformatter.SetHashAlgorithm("MD5");
                if (RSADeformatter.VerifySignature(HashbyteDeformatter, DeformatterData))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        /// <summary>
        /// RSA签名验证
        /// </summary>
        /// <param name="strKeyPublic">公钥</param>
        /// <param name="strHashbyteDeformatter">Hash描述</param>
        /// <param name="DeformatterData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureDeformatter(string strKeyPublic, string strHashbyteDeformatter, byte[] DeformatterData)
        {
            try
            {
                byte[] HashbyteDeformatter;
                HashbyteDeformatter = Convert.FromBase64String(strHashbyteDeformatter);
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPublic);
                System.Security.Cryptography.RSAPKCS1SignatureDeformatter RSADeformatter = new System.Security.Cryptography.RSAPKCS1SignatureDeformatter(RSA);
                //指定解密的时候HASH算法为MD5 
                RSADeformatter.SetHashAlgorithm("MD5");
                if (RSADeformatter.VerifySignature(HashbyteDeformatter, DeformatterData))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        /// <summary>
        /// RSA签名验证
        /// </summary>
        /// <param name="strKeyPublic">公钥</param>
        /// <param name="HashbyteDeformatter">Hash描述</param>
        /// <param name="strDeformatterData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureDeformatter(string strKeyPublic, byte[] HashbyteDeformatter, string strDeformatterData)
        {
            try
            {
                byte[] DeformatterData;
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPublic);
                System.Security.Cryptography.RSAPKCS1SignatureDeformatter RSADeformatter = new System.Security.Cryptography.RSAPKCS1SignatureDeformatter(RSA);
                //指定解密的时候HASH算法为MD5 
                RSADeformatter.SetHashAlgorithm("MD5");
                DeformatterData = Convert.FromBase64String(strDeformatterData);
                if (RSADeformatter.VerifySignature(HashbyteDeformatter, DeformatterData))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        /// <summary>
        /// RSA签名验证
        /// </summary>
        /// <param name="strKeyPublic">公钥</param>
        /// <param name="strHashbyteDeformatter">Hash描述</param>
        /// <param name="strDeformatterData">签名后的结果</param>
        /// <returns></returns>
        public bool SignatureDeformatter(string strKeyPublic, string strHashbyteDeformatter, string strDeformatterData)
        {
            try
            {
                byte[] DeformatterData;
                byte[] HashbyteDeformatter;
                HashbyteDeformatter = Convert.FromBase64String(strHashbyteDeformatter);
                System.Security.Cryptography.RSACryptoServiceProvider RSA = new System.Security.Cryptography.RSACryptoServiceProvider();
                RSA.FromXmlString(strKeyPublic);
                System.Security.Cryptography.RSAPKCS1SignatureDeformatter RSADeformatter = new System.Security.Cryptography.RSAPKCS1SignatureDeformatter(RSA);
                //指定解密的时候HASH算法为MD5 
                RSADeformatter.SetHashAlgorithm("MD5");
                DeformatterData = Convert.FromBase64String(strDeformatterData);
                if (RSADeformatter.VerifySignature(HashbyteDeformatter, DeformatterData))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion
        #endregion
    }
}
