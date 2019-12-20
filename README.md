# 可於Console執行的MRP程式

### 在專案資料夾執行make可以編譯及連結libknifour.a

### 資料夾說明
### 在各個資料夾編譯、連結前必須先編譯連結libknifour.a

##### exam    測試用小程式，執行make可編譯、連結test執行檔

##### include 專案要用到的所有標頭檔

##### mysql   自己寫的mysql公用程式，執行make可編譯、連結myhello執行檔

##### ncurses 有用到ncurses的測試程式，共有四個目標
#####         make會編譯、連結hello執行檔
#####         make test    會編譯、連結test執行檔
#####         make twinkle 會編譯、連結twinkle執行檔
#####         make win     會編譯、連結win執行檔

##### schar  螢幕字元類別，SCHAR為超類別，UTF8SCHAR為儲存UTF8編碼的螢幕字元

#####        執行make可編譯、連結test執行檔

##### screen 螢幕類別，執行make可編譯、連結test執行檔

##### util   專案會用到的公用程式，執行make可編譯、連結test執行檔
