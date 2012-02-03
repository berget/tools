自动测试Linode机房的访问速度

#. 自动获取最新的Linode机房列表
#. 获取ping值列表，去除最高值、最低值后求平均
#. 从各个机房下载100MB的文件，计算平均下载速度

测试报告包括

#. 各个机房ping值，从小到大排序
#. 各个机房下载速度，从大到小排序

Note: 广告时间，如果你有兴趣注册Linode并购买VPS，欢迎使用我的Referer链接: http://www.linode.com/?r=2e236898b83cd7963f1cb6136e7b00cb9f13d1d8 ，非常感谢

以下是杭州电信网络下的测试结果，仅供参考。

== Run SpeedTest For Linode Facilities ==

Example

> $ ./speedtest.py 
> facility     hostname             url                                           
> London, UK   london1.linode.com   http://london1.linode.com/100MB-london.bin    
> Newark, NJ   newark1.linode.com   http://newark1.linode.com/100MB-newark.bin    
> Atlanta, GA  atlanta1.linode.com  http://atlanta1.linode.com/100MB-atlanta.bin  
> Dallas, TX   dallas1.linode.com   http://dallas1.linode.com/100MB-dallas.bin    
> Fremont, CA  fremont1.linode.com  http://fremont1.linode.com/100MB-fremont.bin  
> 
> - ping -c 7 london1.linode.com ...
> - ping -c 7 newark1.linode.com ...
> - ping -c 7 atlanta1.linode.com ...
> - ping -c 7 dallas1.linode.com ...
> - ping -c 7 fremont1.linode.com ...
> 
> show ping result as follow
> facility     time(ms)  
> Fremont, CA  182.0856  
> Newark, NJ   278.9192  
> Dallas, TX   399.7634  
> Atlanta, GA  447.9644  
> London, UK   577.1565  
> 
> - downlaod http://london1.linode.com/100MB-london.bin ...
> - downlaod http://newark1.linode.com/100MB-newark.bin ...
> - downlaod http://atlanta1.linode.com/100MB-atlanta.bin ...
> - downlaod http://dallas1.linode.com/100MB-dallas.bin ...
> - downlaod http://fremont1.linode.com/100MB-fremont.bin ...
> show download speed as follow
> Facility     Speed(kB/s)    
> Fremont, CA  246.162671908  
> Dallas, TX   218.182694595  
> Newark, NJ   202.585620003  
> Atlanta, GA  147.849741751  
> London, UK   62.0631526437  
> 
> Done
