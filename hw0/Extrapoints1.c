void insertOrUpdate(Node** head, char c) {
    if (*head == NULL) {
        *head = createNode(c);
        return;
    }
    
    Node* current = *head;
    while (current != NULL) {
        if (current->data == c) {
            current->count++;
            return;
        }
        if (current->next == NULL) break;
        current = current->next;
    }
    current->next = createNode(c);
}
