// 获取当前页面的 URL
var currentURL = window.location.href;

// 检查是否有跳转标志在 sessionStorage
var redirected = sessionStorage.getItem('redirected');

// 判断是否在首页以及是否已经跳转过
if (currentURL === "https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/" && !redirected) {
    // 获取用户的浏览器语言
    var userLang = navigator.language || navigator.userLanguage;

    // 切割语言代码，只保留前两个字符（例如，从"en-US"变为"en"）
    userLang = userLang.substr(0, 2);

    // 根据浏览器语言设置不同的链接
    var link;

    switch (userLang) {
        case "de": // 德语
            link = "https://docs.sunfounder.com/projects/ultimate-sensor-kit/de/latest/";
            break;
        case "ja": // 日语
            link = "https://docs.sunfounder.com/projects/ultimate-sensor-kit/ja/latest/";
            break;
        default: // 默认（英语）
            link = "https://docs.sunfounder.com/projects/ultimate-sensor-kit/en/latest/";
    }

    // 设置跳转标志
    sessionStorage.setItem('redirected', 'true');

    // 如果不是英语页面或者当前页面不是目标链接，才执行跳转
    if (userLang !== "en" || currentURL !== link) {
        window.location.href = link;
    }
}
