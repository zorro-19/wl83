
@rem �ŵ�����Ŀ¼��
@rem ��� sdk.elf ��ʹ�õĿռ��С��
@rem           ����ַ��������� symbol_tbl.txt ��

set OBJSIZEDUMP=C:\JL\pi32\bin\llvm-objsizedump.exe
set ELF=sdk.elf
set OUTPUT=symbol_tbl.txt

%OBJSIZEDUMP% -lite -skip-zero -enable-dbg-info %ELF% | sort > %OUTPUT%
