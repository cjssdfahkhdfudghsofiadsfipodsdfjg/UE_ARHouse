// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLibrary.h"
#include "Json.h"

FString UJsonParseLibrary::JsonParse(const FString& originData)
{
	FString parsedData;

	// Reader�� ����� �о������
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	//  Reader�� �Ľ̵� ����� ���� json Object�� �����Ѵ�
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	// �ص��Ѵ�

	if (FJsonSerializer::Deserialize(reader, result))
	{
		// items��� �迭����
		TArray<TSharedPtr<FJsonValue>> parsedDataArr = result->GetArrayField("items");

		// �� �ȿ� �ִ� ���뿡�� bookName�� authorName�� �˰� �;
		for (TSharedPtr<FJsonValue> pd : parsedDataArr)
		{
			FString bookName = pd->AsObject()->GetStringField("bk_nm");
			FString authorName = pd->AsObject()->GetStringField("aut_nm");

			// �� ���� ���� ���� ��ȯ�� ���ڿ� �����Ϳ� �߰��� �ֱ�
			parsedData.Append(FString::Printf(TEXT("Book Name : %s\nAuthor Name : %s\n\n"), *bookName, *authorName));
		}
	}

	return parsedData;
}

FString UJsonParseLibrary::MakeJson(const TMap<FString, FString> source)
{
	// json object�� �����ϰ� ���� �ִ´�
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> kv : source)
	{
		jsonObj->SetStringField(kv.Key, kv.Value);
	}

	// Writer�� �����ϰ�, json object�� ���ڵ��Ѵ�
	FString jsonData;

	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);
	FJsonSerializer::Serialize(jsonObj.ToSharedRef(), writer);

	return jsonData;

}
