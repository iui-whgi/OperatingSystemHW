# os_hw

1. 'ctrl + alt + t'로 terminal 열기

![image](https://github.com/user-attachments/assets/540045f7-613b-47db-971f-fa5f9d79f961)

2. update 및 git 설치

       sudo apt update # 비밀번호 1
       sudo apt install -y git  
       
3. git clone
   
   **<>code** -> HTTPS -> web URL 확인

   ![image](https://github.com/user-attachments/assets/e22d1794-14fc-43cb-9f5e-2c598e82c866)

   
       # 형식 git clone [web URL]
       git clone https://github.com/woosy123/os_hw.git

4. ls로 현재 directory에 os_hw 폴더 생성 확인       

   #### ls
   현재 directory에 있는 file 및 directory 목록 출력

   ![image](https://github.com/user-attachments/assets/a40fdcb5-3d64-4560-aed5-05bd9456f1c8)

   os_hw 폴더 확인

   
6. os1.c, os2.c 파일 수정

       cd os_hw
       vi [파일명] #예 vi os1.c

8. C 컴파일하기

   a) gcc 설치

   gcc :  다양한 프로그래밍 언어를 위한 오픈소스 컴파일러
   
       sudo apt install -y gcc

   b) 실행파일 생성

       gcc [파일명] #예 gcc os1.c
       ls 

   코드에 문제가 없다면 정상적으로 a.out이 생성됨

   c) a.out 실행 w. test1.bin

       cat test1.bin | ./a.out

   test1.bin 파일의 내용을 표준 입력(stdin)을 통해 ./a.out 실행 파일로 전달
    

       
## 참고

### vi 사용법

1. 파일 열기

       vi [파일명]

2. i 또는 a로 입력모드 전환 -> 코드 작성
   
3. 파일 닫기

   ESC 누른 후,

   a) 수정 후 저장 ':wq'
   
   b) 종료 : ':q'

   c) 저장하지 않고 강제 종료 ':q!'


### 명령어 참고

ls 명령어  - <https://rhrhth23.tistory.com/4>

vi 명령어 - <https://velog.io/@zeesoo/Linux-vi-%ED%8E%B8%EC%A7%91%EA%B8%B0-%EC%82%AC%EC%9A%A9%EB%B2%95-%EB%B0%8F-%EB%AA%85%EB%A0%B9%EC%96%B4>

