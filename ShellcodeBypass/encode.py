shellcode = b""

str_=""
for i in shellcode:
    code=(i^1024)+1024
    str_+=str(code)

with open("ii.php","w") as f:
    f.write(f'<?php header("sc:{str_}");?>')
print("ok")


