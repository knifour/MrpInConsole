const jsonMenu = '[{"menuname":"基本資料","menuitem":[{"itemname":"零件資料管理","itemproc":"PARCRE","itemdesc":"零件資料建立、查詢、修改、刪除。"},{"itemname":"零件庫存調整管理","itemproc":"RSVHDL","itemdesc":"庫存調整用於電腦庫存與實際庫存不一時之盤盈、盤損處理。"},{"itemname":"零件資料列印","itemproc":"PARPRT","itemdesc":"零件庫存資料列印。"},{"itemname":"零件資料列印-廠商","itemproc":"PARPRT1","itemdesc":"零件庫存資料列印（依廠商列印）。"},{"itemname":"零件資料列印-採購","itemproc":"PARPRT2","itemdesc":"零件庫存資料列印（庫存小於需求）。"},{"itemname":"庫存總金額計算","itemproc":"PARCLC","itemdesc":"計算零件之庫存總金額。"},{"itemname":"產品資料管理","itemproc":"GODCRE","itemdesc":"產品資料建立、查詢、修改、刪除。"},{"itemname":"產品價格資料管理","itemproc":"GODPCRE","itemdesc":"產品價格資料建立、查詢、修改、刪除。"},{"itemname":"產品資料列印","itemproc":"GODPRT","itemdesc":"產品資料列印。"},{"itemname":"客戶資料管理","itemproc":"CUSCRE","itemdesc":"客戶資料建立、查詢、修改、刪除。"},{"itemname":"客戶資料列印","itemproc":"CUSPRT","itemdesc":"客戶資料列印。"},{"itemname":"廠商資料管理","itemproc":"SUPCRE","itemdesc":"廠商資料建立、查詢、修改、刪除。"},{"itemname":"廠商資料列印","itemproc":"SUPPRT","itemdesc":"廠商資料列印。"},{"itemname":"加工品資料建檔","itemproc":"OEMCRE","itemdesc":"輸入加工品號、品名、單價等資料。"},{"itemname":"加工明細管理","itemproc":"OMOCRE","itemdesc":"輸入加工人員加工明細。"},{"itemname":"成本項目管理","itemproc":"ITMCRE","itemdesc":"成本項目建立、查詢、修改、刪除。"}]},{"menuname":"規格表","menuitem":[{"itemname":"零件規格表管理","itemproc":"BOMCRE","itemdesc":"零件規格表建立、查詢、修改、刪除。"},{"itemname":"零件規格表列印","itemproc":"BOMPRT","itemdesc":"零件規格表列印。"},{"itemname":"零件規格表列印(一)","itemproc":"BOMPRT1","itemdesc":"零件規格表列印（可多品號連續列印，無法列印二階）。"},{"itemname":"零件規格表查詢","itemproc":"BOMINQ","itemdesc":"查詢某一特定零件使用在那些機種。"},{"itemname":"零件規格表比對","itemproc":"BOMREF","itemdesc":"比對兩個產品的零件規格表有那些不同。"},{"itemname":"零件用量明細","itemproc":"PARDTL","itemdesc":"列印單一零件用量明細表。"},{"itemname":"零件用量明細(一)","itemproc":"PARDTL1","itemdesc":"列印某段期間所有零件之總用量。"},{"itemname":"生產報表管理","itemproc":"PRDCRE","itemdesc":"建立、修改、刪除每日生產報表。"},{"itemname":"機種庫存明細","itemproc":"GODRSV","itemdesc":"計算特定機種的零件庫存金額。"},{"itemname":"自動計算庫存數量","itemproc":"RSVAUTO","itemdesc":"跟據上次庫存調整後之進貨、出貨及不良品數量自動計算庫存。"}]},{"menuname":"訂單管理","menuitem":[{"itemname":"訂單資料建檔","itemproc":"ORDCRE","itemdesc":"訂單資料建立。"},{"itemname":"訂單資料管理","itemproc":"ORDINQ","itemdesc":"訂單資料查詢、修改、刪除、取消、列印。"},{"itemname":"訂單備料明細","itemproc":"NEDPRT","itemdesc":"以下單日列印出本日之材料需求明細。"},{"itemname":"訂單資料查詢","itemproc":"ORDINQ1","itemdesc":"可查詢某一特定訂單項次之出貨情形。"},{"itemname":"模擬發料","itemproc":"USETST","itemdesc":"可查詢某一特定期間訂單之零件需求及庫存。"},{"itemname":"折讓單作業","itemproc":"DISCRE","itemdesc":"輸入、修改、刪除、列印折讓單。"}]},{"menuname":"進貨","menuitem":[{"itemname":"採購資料建檔","itemproc":"IRDCRE","itemdesc":"自行輸入。"},{"itemname":"採購資料建檔(一)","itemproc":"IRDCRE1","itemdesc":"依電腦計算之當日零件需求拉單。"},{"itemname":"採購資料管理","itemproc":"IRDINQ","itemdesc":"採購資料查詢、修改、刪除、列印。"},{"itemname":"採購單列印","itemproc":"IRDINQ1","itemdesc":"可查詢及列印某一特定廠商之採購單。"},{"itemname":"在途訂單查詢(零件)","itemproc":"IRDINQ2","itemdesc":"以零件查詢在途訂單。"},{"itemname":"在途訂單查詢(廠商)","itemproc":"IRDINQ3","itemdesc":"以廠商查詢在途訂單。"},{"itemname":"進貨資料管理","itemproc":"INNCRE","itemdesc":"進貨資料建立、查詢、修改、刪除。"},{"itemname":"列印進貨資料","itemproc":"INNPRT","itemdesc":"列印某一家廠商某一段期間的進貨資料。"},{"itemname":"列印進貨總表","itemproc":"INNSUM","itemdesc":"列印某一段期間所有廠商進貨金額。"},{"itemname":"不良品(售料)","itemproc":"NOGCRE","itemdesc":"不良品資料輸入及售料管理。"},{"itemname":"未進貨資料列印","itemproc":"IRDYET","itemdesc":"可單一或全部列印某一段期間之未進貨廠商。"},{"itemname":"採購尾數取消","itemproc":"IRDCNL","itemdesc":"將某一採購單之尾數取消。"},{"itemname":"進貨達成率表","itemproc":"INNRTE","itemdesc":"以交期為依據列印當月份之交貨達成率。"},{"itemname":"進貨金額查詢","itemproc":"INNPRT1","itemdesc":"查詢某一段期間的進貨總金額。"}]},{"menuname":"出貨","menuitem":[{"itemname":"領料單管理","itemproc":"USECRE","itemdesc":"以項次建立領料單資料。"},{"itemname":"領料單查詢","itemproc":"USEINQ","itemdesc":"以起始、終止項次查詢、修改、列印領料單資料。"},{"itemname":"單品領料單","itemproc":"WRKCRE","itemdesc":"訂單無關零件之領料處理及剩餘之零件入庫。"},{"itemname":"出貨資料建立","itemproc":"OUTCRE","itemdesc":"出貨資料建立。"},{"itemname":"出貨資料查詢","itemproc":"OUTINQ","itemdesc":"出貨資料查詢、修改、刪除。"},{"itemname":"銷貨退回","itemproc":"RTOCRE","itemdesc":"輸入銷貨退回資料，方便扣帳。"},{"itemname":"列印出貨資料","itemproc":"OUTPRT","itemdesc":"列印某一家客戶某一段期間的出貨資料。"},{"itemname":"列印出貨資料(一)","itemproc":"OUTPRT1","itemdesc":"列印某一家客戶某一段期間的出貨資料（相同品號自動整合）。"},{"itemname":"列印出貨總表","itemproc":"OUTSUM","itemdesc":"列印某一段期間所有客戶出貨資料。"},{"itemname":"未出貨資料列印","itemproc":"YETPRT","itemdesc":"列印已訂貨且未出貨之資料。"},{"itemname":"未出貨資料(品號)","itemproc":"YETPRT1","itemdesc":"以品號查詢未出貨資料。"},{"itemname":"未出貨資料列印(二)","itemproc":"YETPRT2","itemdesc":"列印已訂貨且未出貨之資料，可依產品編號排序（以客戶、及交期查詢）。"},{"itemname":"各機種出貨表","itemproc":"OUTDTL","itemdesc":"列印單一機種出貨明細表。"},{"itemname":"各機種出貨表(一)","itemproc":"OUTDTL1","itemdesc":"列印單一或全部機種出貨總數量。"},{"itemname":"交貨達成率表","itemproc":"OUTRTE","itemdesc":"以交期為依據列印當月份之交貨達成率。"}]},{"menuname":"其它","menuitem":[{"itemname":"人員資料設定","itemproc":"MEMBER","itemdesc":"設定人員資料及密碼。"},{"itemname":"使用權限設定","itemproc":"PWRCRE","itemdesc":"設定各人員之使用權限。"},{"itemname":"員工資料管理","itemproc":"LBRCRE","itemdesc":"員工資料建立、查詢、修改、刪除。"}]}]';
const objjsonMenu = JSON.parse(jsonMenu);