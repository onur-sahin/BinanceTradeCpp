

SELECT to_timestamp(open_time/1000) AT TIME ZONE 'UTC' as open_time_datetime , * FROM public.tbl_btcusdt_5m
ORDER BY open_time ASC

