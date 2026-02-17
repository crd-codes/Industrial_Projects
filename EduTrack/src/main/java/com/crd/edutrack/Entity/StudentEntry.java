package com.crd.edutrack.Entity;

import lombok.Getter;
import lombok.Setter;
import org.bson.types.ObjectId;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "students")
@Getter
@Setter
public class StudentEntry
{
    @Id
    private String id;      // unique student ID

    private String batchId;   // links to BatchEntry.id
    private String name;
    private int rollNo;



}
