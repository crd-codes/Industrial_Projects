package com.crd.edutrack.Service;

import com.crd.edutrack.Entity.StudentEntry;
import com.crd.edutrack.Repository.StudentEntryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;
import java.util.Optional;

@Service
public class StudentEntryService {

    @Autowired
    private StudentEntryRepository studentRepo;

    // Create student
    public StudentEntry createStudent(StudentEntry student) {
        return studentRepo.save(student);
    }

    // Get students all
    public List<StudentEntry> getAllStudents() {
        return studentRepo.findAll();
    }

    // Get students by batch
    public List<StudentEntry> getStudentsByBatch(String batchId) {
        return studentRepo.findByBatchId(batchId);
    }

    // Update student
    public StudentEntry updateStudent(String id, StudentEntry studentDetails) {
        Optional<StudentEntry> optional = studentRepo.findById(id);
        if (optional.isPresent()) {
            StudentEntry student = optional.get();
            student.setName(studentDetails.getName());
            student.setRollNo(studentDetails.getRollNo());
            return studentRepo.save(student);
        } else {
            return null;
        }
    }

    // Delete student
    public boolean deleteStudent(String id) {
        if (studentRepo.existsById(id)) {
            studentRepo.deleteById(id);
            return true;
        }
        return false;
    }
}
