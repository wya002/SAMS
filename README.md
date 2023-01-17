# 🚀SAMS : Surface to Air Missile System
## 👍 미니 프로젝트 : 대공유도탄 모의 시스템
### 👏 만든이들
|이름|GitHub|역할|
|---|---|---|
|강준희🤷‍♂️|<https://github.com/jhkang>|MSS(MiSsile Simulator)|
|하태민🤷‍♂️|<https://github.com/TaeMin15>|ATS(AirThreat Simulator)|
|이채현🤷‍♂️|<https://github.com/xmfxhddl>|UDP, GUI(OpenCV)|
|장우진🤷‍♀️|<https://github.com/W00JIN>|TCC(TestControl Computer)|
|우용안🤷‍♂️|<https://github.com/wya002>|GUI, C#|
+ 🖼️openCV 구현 코드 - https://github.com/xmfxhddl/SAMS_opencv
#
### 📒 적용 기술
|기술|적용 분야|
|---|---|
|C++|UDP통신, TCC,ATS,MSS 구현 및 모의기간 데이터 교환|
|C#|GUI 이벤트 구현 및 모의기로 부터 받아온 값 설정|
|WPF|GUI 구현|
|OpenCV|지도상의 설정된 좌표간 드로잉 구현|
## 🚀시스템 개요
 * 대공유도탄 모의 시스템은 공중위협에 대응하여 지대공 유도탄 발사를 통해 교전 하는 모의 시스템이다.
 * 사용자로부터 공중위협의 시작좌표와 목표좌표 및 대공 유도탄 발사대 위치 좌표를 입력받아 시나리오를 실행한다.
 * 사용자가 설정한 시나리오는 XML파일로 저장 가능하며, 이미 만들어진 시나리오를 불러와 실행 가능하다.
 * 공중위협의 위치가 대공 유도탄 발사대의 레이다 탐지 범위내에 들어올 경우 대공 유도탄 발사 버튼이 활성화 되며, 사용자의 컨트롤에 의해 발사된다.
#
## 🚀메인 화면 (TCC)

<img src="https://user-images.githubusercontent.com/75249093/207766901-d5613473-e2b6-4f2c-a804-fa16cbf2585d.png" width="600" height="400"/>



#
## 🚀시나리오 시연 화면

<img src="https://user-images.githubusercontent.com/75249093/207768313-c2c9eddf-90b5-4ba0-89b4-c0896dcd39b7.gif" width="600" height="400"/>

#
