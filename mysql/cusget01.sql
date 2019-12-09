SELECT
  CusNum as `編號`,
	CusNme as `簡稱`,
	CusRch as `連絡人`,
	CusTel as `電話`
from CUSTOM
  where CusNum like 'Z%';