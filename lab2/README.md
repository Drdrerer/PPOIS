
**Классы:**

1.  **Accountant** (полей: 3, методов: 4) -> AccountingDepartment, Invoice, RepairOrder, Payment, FinancialReport
2.  **AccountingDepartment** (полей: 3, методов: 4) -> Invoice, TaxReport, FinancialReport, Payment
3.  **Address** (полей: 3, методов: 3) ->
4.  **Carpenter** (полей: 3, методов: 4) -> Tool
5.  **Client** (полей: 3, методов: 3) -> RepairOrder, Review
6.  **ClientServiceDepartment** (полей: 3, методов: 4) -> Client, Complaint, Review, RepairOrder, Manager
7.  **CustomerService** (полей: 3, методов: 4) -> ClientServiceDepartment, Client, Complaint
8.  **Delivery** (полей: 3, методов: 3) -> Material, Supplier
9.  **Department** (полей: 3, методов: 1) -> Employee
10. **Electrician** (полей: 3, методов: 4) -> Specialization
11. **Employee** (полей: 3, методов: 3) ->
12. **FinancialReport** (полей: 4, методов: 3) -> Payment
13. **HRDepartment** (полей: 3, методов: 5) -> Employee, Qualification, WorkSchedule
14. **InventoryItem** (полей: 3, методов: 2) -> Material
15. **Invoice** (полей: 3, методов: 3) ->
16. **LegalEntityClient** (полей: 3, методов: 2) ->
17. **Logistician** (полей: 3, методов: 4) -> LogisticsDepartment, Delivery, SupplyRequest, Supplier, Route
18. **LogisticsDepartment** (полей: 3, методов: 4) -> Supplier, Delivery, Vehicle, Material
19. **Manager** (полей: 3, методов: 5) -> ClientServiceDepartment, RepairOrder, Client, RepairObject, Team, Notification
20. **Master** (полей: 3, методов: 5) -> Qualification, Team, RepairTask
21. **Material** (полей: 3, методов: 2) -> MaterialCategory
22. **MaterialCategory** (полей: 3, методов: 3) -> Material
23. **Notification** (полей: 3, методов: 3) ->
24. **OrderStatus** (полей: 3, методов: 1) ->
25. **Painter** (полей: 3, методов: 4) -> Sprayer, PaintType
26. **Payment** (полей: 3, методов: 2) ->
27. **Plumber** (полей: 3, методов: 4) -> Specialization, Tool
28. **PriceList** (полей: 3, методов: 3) -> PriceListItem, Service
29. **PriceListItem** (полей: 3, методов: 2) -> Service
30. **PrivateClient** (полей: 3, методов: 2) ->
31. **Qualification** (полей: 3, методов: 3) ->
32. **RepairFirm** (полей: 3, методов: 5) -> Department, FinancialReport
33. **RepairObject** (полей: 3, методов: 2) -> Address
34. **RepairOrder** (полей: 4, методов: 5) -> Client, RepairTask
35. **RepairStage** (полей: 3, методов: 3) -> Material, Master
36. **RepairTask** (полей: 3, методов: 3) -> Service
37. **Review** (полей: 3, методов: 3) -> RepairOrder
38. **Roofer** (полей: 3, методов: 4) -> RoofType
39. **Service** (полей: 3, методов: 2) -> RepairObject
40. **Specialization** (полей: 3, методов: 1) -> Qualification
41. **Supplier** (полей: 3, методов: 3) -> Material
42. **SupplyRequest** (полей: 3, методов: 3) -> Material, Supplier, Manager
43. **TaskAssignment** (полей: 3, методов: 3) -> Master, RepairTask
44. **TaxReport** (полей: 3, методов: 2) ->
45. **Team** (полей: 3, методов: 6) -> Master, RepairTask, Material
46. **Tool** (полей: 3, методов: 3) ->
47. **Warehouse** (полей: 3, методов: 4) -> InventoryItem, Material, Delivery
48. **Warehouseman** (полей: 3, методов: 4) -> Warehouse, SupplyRequest, RepairTask, Material
49. **WorkSchedule** (полей: 3, методов: 3) -> WorkShift, Team, Employee
50. **WorkShift** (полей: 3, методов: 3) -> Master

**Исключения:**

1.  **ClientBlacklistedException** (полей: 0, методов: 1)
2.  **DoubleAssignmentException** (полей: 0, методов: 1)
3.  **DuplicateEmployeeIdException** (полей: 0, методов: 1)
4.  **InsufficientFundsException** (полей: 0, методов: 1)
5.  **InvalidOrderStatusException** (полей: 0, методов: 1)
6.  **InvalidRepairObjectAddressException** (полей: 0, методов: 1)
7.  **MaterialNotAvailableException** (полей: 0, методов: 1)
8.  **NegativeInventoryException** (полей: 0, методов: 1)
9.  **QualificationMismatchException** (полей: 0, методов: 1)
10. **ScheduleConflictException** (полей: 0, методов: 1)
11. **TaskAlreadyCompletedException** (полей: 0, методов: 1)
12. **UnapprovedSupplierException** (полей: 0, методов: 1)

---

**Всего:**
* **Классов:** 50
* **Исключений:** 12
* **Полей:** 152
* **Методов:** 187 + Set и Get функции
* **Ассоциаций:** 88
