package com.crd.edutrack.Repository;

import com.crd.edutrack.Entity.StudentEntry;
import org.springframework.data.mongodb.repository.MongoRepository;
import java.util.List;

public interface StudentEntryRepository extends MongoRepository<StudentEntry, String>
{
    List<StudentEntry> findByBatchId(String batchId);
}
