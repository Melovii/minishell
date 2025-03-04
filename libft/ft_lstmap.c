#include "libft.h"

void static	ft_lstmap_helper_func(t_list **head, t_list **lst, t_list *new_node)
{
	t_list	*temp;

	temp = *lst;
	ft_lstadd_back(head, new_node);
	*lst = temp -> next;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			free(new_content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstmap_helper_func(&head, &lst, new_node);
	}
	return (head);
}
