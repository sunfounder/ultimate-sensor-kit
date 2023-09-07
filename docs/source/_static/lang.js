// 获取当前页面的 URL
var currentURL = window.location.href;

// 判断是否在首页
if (currentURL === "https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/") {
    // 获取用户的浏览器语言
    var userLang = navigator.language || navigator.userLanguage;

    // 切割语言代码，只保留前两个字符（例如，从"en-US"变为"en"）
    userLang = userLang.substr(0, 2);

    // 根据浏览器语言设置不同的链接
    var link;

    switch (userLang) {
        case "de": // 德语
            link = "https://docs.sunfounder.com/projects/ultimate-sensor-kit/ja/latest/";
            break;
        case "ja": // 日语
            link = "https://docs.sunfounder.com/projects/ultimate-sensor-kit/de/latest/";
            break;
        default: // 默认（英语）
            link = "https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/";
    }

    // 用JavaScript自动跳转到相应的链接
    window.location.href = link;
}
