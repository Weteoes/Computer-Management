package Weteoes.Model.Config;


public class InitializationClass {
    class rsa_{
        public String c_PrivateKey = "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCkuGCqv6siMrpRdm5fFSVlnEZNjyYQLm9lV/a5vYw9pO8QS1QyF5ycm7T94sLKP71X/i4JoB3nyFp88vh0nB+7sHlWqQLq3RgeEbiBwqcZWMg3YY9tPll6RYawb7osJWUO8YjmqBIN5qUfXJ9ZpcN2kxbqrrY8hoIv1SLOWm4eLviCjp3hCeZjf8QuiKcp7osY8Y4ZuYhqIE2YN7H5fw0pRcaJwSFwQj5+n52EUhFvI6rdYW7SHVd1t3PaPkQt+kdcycHfpd2roz5Rp4v/QUcFmDQJ3OAHWzOyZphcxLJ1C5yEzlmXTlQMLejFxI1/+iCuLltMyRbIXIx1RIDIOCR3AgMBAAECggEAK0h7tkJ5MJpN1TwekoOW+RVQb+7unI/nG6U6ouII6OXfH9P7gtIriAduTsx4TPbkxSt4Y3UchpxiErUxzkp8GDCuIbR1nMuOG9CiQA6rJADtU4giTR12G6gLVW92Z0VIQd38EEgXvmld+Fi5UrA5JX5PJknUfyEFMpZ59+lRSEK5hEsFfKMMKaJ+Wrat2q/OF3gu7zyNB6OJvcZl7U2SfKop+PBMhWjNbzb4aq5ZT4at/0ehV/eikMF1SBw2336Gg2VIXgz1SuHrfslOGbEQ5wCWAgCzdI1D7rGr1MrtlO8pEEEzMvrZo0M/ZXyApr8jyBPVCTpkdW00331IDNKiKQKBgQDOuc1usMv3rqgX6VygVm/EYcoLtwIQr1h1i/EA9R922yX0I0wr9an62yrE+wJhoPE0kX+FWJgGvwydg8CTmiyplJsuKX3YEKUzFAVzqZSlEs5cCmqnMJeAQgx0aYizyPL5BE7/WZTSC9G7Rg79YkPaT/eH5mfsGdOFQB19Sd+O2wKBgQDL+3AvYwPIBBxd7PG+xG01WxZ3pXxQSdak9xczTasIdFGzhd0hRvY7V9+0fhdceI6ETOYcFUSF8PwP6ytGeKNLP94gx+anIxkuzbaYq0/7RkvEyGNwV9x5giMhSETdLqJ45+nQH1azuZ3UQ8mhIijwpmCceIJZ8S6+vhOuLbCtlQKBgGaqCab2MGWSHLK7Vx/drWYG9pN40JK+shy2YfsKwRSC40dqnDKcr00AuS3YRqd7iS6FL6JmjCGVkctMGkBzacjSH3r+ahv6sEA8qjR1vHd6bndxSOQ9EpBEvPC3VIeMvXYDuMPBllH2QrNRqLIXsgDig9i/CU9MyCo93CdTn63PAoGBAJVuCw8L0BdUu5srGyWPLBmsMtdPibQfg3ix8nMI8MRuwfNrm0TngTaT9zN4M5DwWCcfVms4QUyF74GR28/yTF2x2f3Vs2i5U5dv59YLmboQEy2DRyVjmAYDicy17ozBvxAnhKeMba2XysFXL3w1VByHJbs6pPNStdXR1QUCP63JAoGAdxr8DHiN6F+3tkZlBuBzELBlpIa6vqHWIYJPuRw1SN3jlb98pw4ubLQaR/DJpQbaOiFB7bqtZ3WTxs/aX8Bi9UfXvheThnvkEfRtIqtObm1VARHZrEqSHnX0EL0FKYwUzTLP9kEJTNUA5HSb8Ss6hIJGp8UYJuS6Vvo27B1g9cE=";
        public String c_PublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApLhgqr+rIjK6UXZuXxUlZZxGTY8mEC5vZVf2ub2MPaTvEEtUMhecnJu0/eLCyj+9V/4uCaAd58hafPL4dJwfu7B5VqkC6t0YHhG4gcKnGVjIN2GPbT5ZekWGsG+6LCVlDvGI5qgSDealH1yfWaXDdpMW6q62PIaCL9UizlpuHi74go6d4QnmY3/ELoinKe6LGPGOGbmIaiBNmDex+X8NKUXGicEhcEI+fp+dhFIRbyOq3WFu0h1Xdbdz2j5ELfpHXMnB36Xdq6M+UaeL/0FHBZg0CdzgB1szsmaYXMSydQuchM5Zl05UDC3oxcSNf/ogri5bTMkWyFyMdUSAyDgkdwIDAQAB";
    }
    public String rsa_Code(String data,int type){
        Weteoes.Model.security.RsaClass rsaClass = new Weteoes.Model.security.RsaClass();
        String result = null;
        switch(type){
            case 1: result = rsaClass.byPublicAsEncode(data,new rsa_().c_PublicKey); break;
            case 2: result = rsaClass.byPrivateAsUnEncode(data,new rsa_().c_PrivateKey); break;
        }
        return result;
    }
}
