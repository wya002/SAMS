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