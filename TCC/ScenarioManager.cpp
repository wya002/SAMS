#include "ScenarioManager.h"
#include "tinyxml.h"

void  ScenarioManager::save()
{
	double startX1 = airThreatScenario.getInitPosition().x;
	double startY1 = airThreatScenario.getInitPosition().y;
	double endX2 = airThreatScenario.getTargetPosition().x;
	double endY2 = airThreatScenario.getTargetPosition().y;
	double MSSX = missileScenario.getInitPosition().x;
	double MSSY = missileScenario.getInitPosition().y;

	//xml 선언
	TiXmlDocument doc;
	TiXmlDeclaration* pDec1 = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(pDec1);

	//루트 노드 추가
	TiXmlElement* pRoot = new TiXmlElement("DB");
	doc.LinkEndChild(pRoot);

	int value = 100;

	// 하위노드 및 데이터 추가
	// 시나리오 생성기
	TiXmlElement* pElem = new TiXmlElement("Synario");
	pRoot->LinkEndChild(pElem);

	//하위노드 및 속성 추가
	TiXmlElement* pSubElem = new TiXmlElement("SynarioStart");	// ATS 초기위치
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("Position", "Value");
	pSubElem->SetAttribute("Start", startX1);
	pSubElem->SetAttribute("End", startY1);

	pSubElem = new TiXmlElement("SynarioDestination");			// ATS 목적위치
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("Position", "Value");
	pSubElem->SetAttribute("Start", endX2);
	pSubElem->SetAttribute("End", endY2);

	pSubElem = new TiXmlElement("SynarioMSS");					// MSS 초기위치
	pElem->LinkEndChild(pSubElem);
	pSubElem->SetAttribute("Position", "Value");
	pSubElem->SetAttribute("Start", MSSX);
	pSubElem->SetAttribute("End", MSSY);

	doc.SaveFile("C:/Users/User/Desktop/Test.xml");		// 저장 파일 위치
}

void ScenarioManager::load(int x1, int tx)
{
	TiXmlDocument ReadDoc;
	ReadDoc.LoadFile("C:/Users/User/Desktop/Test.xml");

	// 루트 가져오기
	TiXmlElement* ReadRoot = ReadDoc.FirstChildElement("DB");
	TiXmlElement* sub1 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioStart");
	TiXmlElement* sub2 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioDestination");
	TiXmlElement* sub3 = ReadRoot->FirstChildElement("Synario")->FirstChildElement("SynarioMSS");

	// 노드를 다루기 위한 핸들
	TiXmlHandle handle1(0);
	TiXmlHandle handle2(0);
	TiXmlHandle handle3(0);
	handle1 = TiXmlHandle(sub1);
	handle2 = TiXmlHandle(sub2);
	handle3 = TiXmlHandle(sub3);

	TiXmlAttribute* pAttrib1;
	TiXmlAttribute* pAttrib2;
	TiXmlAttribute* pAttrib3;
	pAttrib1 = sub1->FirstAttribute();
	pAttrib2 = sub2->FirstAttribute();
	pAttrib3 = sub3->FirstAttribute();

	// 초기위치 값 변수 할당
	pAttrib1 = pAttrib1->Next();
	double ATSInitX = pAttrib1->IntValue();
	pAttrib1 = pAttrib1->Next();
	double ATSInitY = pAttrib1->IntValue();

	// 목표위치 값 변수 할당
	pAttrib2 = pAttrib2->Next();
	double ATSEndX = pAttrib2->IntValue();
	pAttrib2 = pAttrib2->Next();
	double ATSEndY = pAttrib2->IntValue();

	// 목표위치 값 변수 할당
	pAttrib3 = pAttrib3->Next();
	double MSSInitX = pAttrib3->IntValue();
	pAttrib3 = pAttrib3->Next();
	double MSSInitY = pAttrib3->IntValue();

	airThreatScenario.setInitPosition({ ATSInitX , ATSInitY });
	airThreatScenario.setTargetPosition({ ATSEndX , ATSEndY });
	missileScenario.setInitPosition({ MSSInitX , MSSInitY });
}
